#!/usr/bin/env python3
"""kxtranspose: reorder a 2004 .kx export for better compression.

Two sections of the 2004 format are interleaved per operator. Stored as
separate streams they compress better with the context-mixing packer:

  * op types + inputs: [type (+input count)] for all ops, then all input
    deltas (instead of type, deltas, type, deltas, ...)
  * parameters (sorted by class): column-major, i.e. every op's parameter 0,
    then every op's parameter 1, ... followed by the strings and spline
    references of the class's ops (instead of all parameters of op 0, op 1..)

KDoc::Init in the size build (KK_SMALL) reads this layout; everything else in
the file stays as it is.

  kxtranspose.py in.kx out.kx        (in.kx: V2 tunes already converted)
"""
import struct, sys

SIZES = {'e': 2, 'i': 4, 's': 2, 'b': 1, 'c': 4, 'm': 3}

def psize(ch, d, p):
    """bytes of one packed parameter (sReadF16/F24 store special values in 1)"""
    if ch == 'g':
        return 1 if d[p] in (0x00, 0x80, 0x01, 0x81) else 2
    if ch == 'f':
        return 1 if d[p] in (0x00, 0x01, 0xff) else 3
    return SIZES.get(ch, 0)

def transpose(d):
    p = 0
    def u32():
        nonlocal p
        v = struct.unpack_from('<I', d, p)[0]; p += 4; return v
    def short():                                   # sReadShort: 7/15 bit varint
        nonlocal p
        v = d[p]; p += 1
        if v & 128:
            v = (v & 127) | (d[p] << 7); p += 1
        return v
    songsize = u32(); p += (songsize + 3) & ~3
    fxsize = u32(); p += (fxsize + 3) & ~3
    nops = short(); nsplines = short()
    classes = []                                   # (conv, id, packing)
    while True:
        conv = struct.unpack_from('<I', d, p)[0]
        if conv == 0:
            break
        p += 4
        cid = d[p]; p += 1
        e = d.index(b'\0', p)
        classes.append((conv, cid, d[p:e].decode('latin1'))); p = e + 1
    p += 4

    # types + inputs -> types stream, input stream
    tstart = p
    types, inputs = bytearray(), bytearray()
    optype = []
    for i in range(nops):
        t = d[p]; p += 1
        types.append(t)
        optype.append(t & 0x7f)
        conv = classes[t & 0x7f][0]
        if t & 0x80:
            n = 0
        elif conv & 0x80000000:                    # OPC_FLEXINPUT
            n = d[p]; p += 1
            types.append(n)
        else:
            n = (conv >> 8) & 15
        for k in range(n):
            q = p; short(); inputs += d[q:p]
    tend = p
    for i in range(nops):                          # links (unchanged)
        for k in range((classes[optype[i]][0] >> 12) & 15):
            short()

    # parameters -> column-major per class
    pstart = p
    params = bytearray()
    for ci, (conv, cid, pack) in enumerate(classes):
        ops = [i for i in range(nops) if optype[i] == ci]
        cols = [[] for _ in pack]
        tails = []
        for i in ops:
            for j, ch in enumerate(pack):
                n = psize(ch.lower(), d, p)
                cols[j].append(d[p:p + n]); p += n
            q = p
            for j in range((conv >> 16) & 15):     # strings
                p = d.index(b'\0', p) + 1
            p += 2 * ((conv >> 20) & 15)           # spline refs
            tails.append(d[q:p])
        for c in cols:
            params += b''.join(c)
        params += b''.join(tails)
    pend = p
    assert len(types) + len(inputs) == tend - tstart and len(params) == pend - pstart

    return (d[:tstart] + bytes(types) + bytes(inputs) + d[tend:pstart] +
            bytes(params) + d[pend:]), (tend - tstart, pend - pstart)

if __name__ == '__main__':
    d = open(sys.argv[1], 'rb').read()
    t, (ti, pa) = transpose(d)
    open(sys.argv[2], 'wb').write(t)
    print('%s: types/inputs (%d bytes) split, parameters (%d bytes) column-major' % (sys.argv[2], ti, pa))
