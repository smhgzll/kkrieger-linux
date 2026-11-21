#!/usr/bin/env python3
"""sidebyside.py a.png b.png out.png  (our own 8-bit RGB, filter-0 PNGs only)"""
import struct, zlib, sys
def load(fn):
    d = open(fn, 'rb').read(); p = 8; idat = b''; w = h = 0
    while p < len(d):
        n = struct.unpack('>I', d[p:p+4])[0]; t = d[p+4:p+8]; c = d[p+8:p+8+n]
        if t == b'IHDR': w, h = struct.unpack('>II', c[:8])
        if t == b'IDAT': idat += c
        p += 12 + n
    raw = zlib.decompress(idat)
    return w, h, [raw[y*(w*3+1)+1:(y+1)*(w*3+1)] for y in range(h)]
wa, ha, ra = load(sys.argv[1]); wb, hb, rb = load(sys.argv[2])
h = max(ha, hb); gap = bytes(3*8)
rows = []
for y in range(h):
    a = ra[y] if y < ha else bytes(wa*3); b = rb[y] if y < hb else bytes(wb*3)
    rows.append(b'\0' + a + gap + b)
W = wa + 8 + wb
def chunk(t, data): return struct.pack('>I', len(data)) + t + data + struct.pack('>I', zlib.crc32(t + data) & 0xffffffff)
open(sys.argv[3], 'wb').write(b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', W, h, 8, 2, 0, 0, 0)) + chunk(b'IDAT', zlib.compress(b''.join(rows), 6)) + chunk(b'IEND', b''))
