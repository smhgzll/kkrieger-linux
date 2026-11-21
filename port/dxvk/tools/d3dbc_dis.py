#!/usr/bin/env python3
"""Minimal Direct3D 9 shader bytecode (SM 1.x / 2.x) disassembler.
usage: d3dbc_dis.py file.ps|file.vs ..."""
import struct, sys

OPS = {  # opcode: (name, number of parameter tokens for SM1)
    0: ('nop', 0), 1: ('mov', 2), 2: ('add', 3), 3: ('sub', 3), 4: ('mad', 4), 5: ('mul', 3),
    6: ('rcp', 2), 7: ('rsq', 2), 8: ('dp3', 3), 9: ('dp4', 3), 10: ('min', 3), 11: ('max', 3),
    12: ('slt', 3), 13: ('sge', 3), 14: ('exp', 2), 15: ('log', 2), 16: ('lit', 2), 17: ('dst', 3),
    18: ('lrp', 4), 19: ('frc', 2), 20: ('m4x4', 3), 21: ('m4x3', 3), 22: ('m3x4', 3), 23: ('m3x3', 3),
    24: ('m3x2', 3), 31: ('dcl', 2), 32: ('pow', 3), 35: ('abs', 2), 36: ('nrm', 2), 37: ('sincos', 2),
    46: ('mova', 2),
    0x40: ('texcoord', 1), 0x41: ('texkill', 1), 0x42: ('tex', 1), 0x43: ('texbem', 2), 0x44: ('texbeml', 2),
    0x45: ('texreg2ar', 2), 0x46: ('texreg2gb', 2), 0x47: ('texm3x2pad', 2), 0x48: ('texm3x2tex', 2),
    0x49: ('texm3x3pad', 2), 0x4a: ('texm3x3tex', 2), 0x4c: ('texm3x3spec', 3), 0x4d: ('texm3x3vspec', 2),
    0x4e: ('expp', 2), 0x4f: ('logp', 2), 0x50: ('cnd', 4), 0x51: ('def', 5), 0x52: ('texreg2rgb', 2),
    0x53: ('texdp3tex', 2), 0x54: ('texm3x2depth', 2), 0x55: ('texdp3', 2), 0x56: ('texm3x3', 2),
    0x57: ('texdepth', 1), 0x58: ('cmp', 4), 0x59: ('bem', 3), 0x5a: ('dp2add', 4), 0xfffd: ('phase', 0),
}
REGT = {0: 'r', 1: 'v', 2: 'c', 3: 't', 4: 'oPos', 5: 'oD', 6: 'oT', 7: 'in', 8: 'oC', 9: 'oDepth', 10: 's'}
SRCMOD = {0: '{}', 1: '-{}', 2: '{}_bias', 3: '-{}_bias', 4: '{}_bx2', 5: '-{}_bx2', 6: '1-{}', 7: '{}_x2',
          8: '-{}_x2', 9: '{}_dz', 10: '{}_dw', 11: 'abs({})', 12: '-abs({})', 13: '!{}'}

def reg(t, vs):
    n = t & 0x7ff
    rt = ((t >> 28) & 7) | ((t >> 8) & 0x18)
    name = REGT.get(rt, 'reg%d_' % rt)
    if vs and rt == 3: name = 'a'
    if rt == 4: return ['oPos', 'oFog', 'oPts'][n] if n < 3 else 'rast%d' % n
    return '%s%d' % (name, n)

def dst(t, vs):
    s = reg(t, vs)
    m = (t >> 16) & 15
    if m != 15: s += '.' + ''.join('xyzw'[i] for i in range(4) if m & (1 << i))
    mod = (t >> 20) & 15
    if mod & 1: s = '_sat ' + s
    shift = (t >> 24) & 15
    if shift: s = ('_x%d ' % (1 << shift) if shift < 8 else '_d%d ' % (1 << (16 - shift))) + s
    return s

def src(t, vs):
    s = reg(t, vs)
    sw = (t >> 16) & 0xff
    if sw != 0xe4:
        comp = ''.join('xyzw'[(sw >> (2 * i)) & 3] for i in range(4))
        if len(set(comp)) == 1: comp = comp[0]
        s += '.' + comp
    return SRCMOD.get((t >> 24) & 15, '{}?').format(s)

def dis(code):
    v = code[0]
    vs = (v >> 16) == 0xfffe
    major, minor = (v >> 8) & 0xff, v & 0xff
    out = ['%s_%d_%d' % ('vs' if vs else 'ps', major, minor)]
    i = 1
    while i < len(code):
        t = code[i]
        if t == 0x0000ffff: break
        op = t & 0xffff
        if op == 0xfffe:
            i += 1 + ((t >> 16) & 0x7fff); continue
        name, n = OPS.get(op, ('op%x' % op, 0))
        if major >= 2: n = (t >> 24) & 15
        elif op == 0x42 and (major, minor) >= (1, 4): n = 2
        args = code[i + 1:i + 1 + n]
        co = '+' if t & 0x40000000 else ''
        if op == 0x51:
            txt = '%sdef %s, %s' % (co, dst(args[0], vs), ', '.join('%.4g' % struct.unpack('<f', struct.pack('<I', a))[0] for a in args[1:]))
        elif op == 31:
            txt = 'dcl_%08x %s' % (args[0], dst(args[1], vs))
        else:
            parts = [dst(args[0], vs)] + [src(a, vs) for a in args[1:]] if args else []
            txt = '%s%s %s' % (co, name, ', '.join(parts))
        out.append('  ' + txt)
        i += 1 + n
    return '\n'.join(out)

if __name__ == '__main__':
    for f in sys.argv[1:]:
        d = open(f, 'rb').read()
        print('==', f); print(dis(list(struct.unpack('<%dI' % (len(d) // 4), d))))
