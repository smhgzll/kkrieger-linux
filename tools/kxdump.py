#!/usr/bin/env python3
"""
kxdump - parser for the *2004* werkkzeug3 export format (.kx) used by
.kkrieger (pno0001.exe). The layout was recovered from the decompiled
KDoc::Init of the original binary (FUN_0081859c); the version in the public
fr_public repository is a later, incompatible revision.

  SongSize u32, SongData[align4]        V2M tune
  SampleSize u32, SampleData[align4]    VFX0 sound effect block
  nOps short, nSplines short            ("short" = 1-2 byte varint)
  class list:  { u32 convention, u8 class id, asciiz packing } ..., u32 0
  per op:      u8 type (bit7 = single implicit input), [u8 ninputs if
               OPC_FLEXINPUT], short delta per input
  per op:      short link (1-based, 0 = none) x OPC_GETLINK(convention)
  op params, grouped by class: packing chars g/f/e/i/s/b/c/m, strings,
               splines (u16, 1-based)
  per op:      animation bytecode (terminated by KA_END)
  events:      short count, {short op, i32 start, i32 end, f24 velocity,
               f24 modulation, u8 select, f24 scale/rotate/translate x3,
               u32 color, short spline(ignored)}
  splines:     u8 (count | interpolation<<3), per channel: short nkeys,
               {u8 time/255, f16 value}

usage: kxdump.py file.kx [--ops] [--oplist kkrieger_oplist.cpp] [--json out.json]
"""
import re, struct, sys, json, argparse

OPC_FLEXINPUT = 0x80000000

def getinput(c): return (c >> 8) & 15
def getlink(c): return (c >> 12) & 15
def getstring(c): return (c >> 16) & 15
def getspline(c): return (c >> 20) & 15
def getdata(c): return c & 0xff

# 2004 anim interpreter: argument bytes per KA_ opcode (table at 0x83f760)
CMDSIZE = [0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
           0, 0, 0, 0, 0, 0, 16, 4, 4, 2, 0, 0, 0, 1]

class R:
    def __init__(self, d, p=0): self.d, self.p = d, p
    def u8(self):
        v = self.d[self.p]; self.p += 1; return v
    def u16(self):
        v = struct.unpack_from('<H', self.d, self.p)[0]; self.p += 2; return v
    def s16(self):
        v = struct.unpack_from('<h', self.d, self.p)[0]; self.p += 2; return v
    def u32(self):
        v = struct.unpack_from('<I', self.d, self.p)[0]; self.p += 4; return v
    def s32(self):
        v = struct.unpack_from('<i', self.d, self.p)[0]; self.p += 4; return v
    def short(self):
        v = self.u8()
        if v & 128: v = (v & 127) | (self.u8() << 7)
        return v
    def f16(self):
        v = self.u8()
        if v == 0x00: return 0.0
        if v == 0x80: return 1.0
        if v == 0x01: return 0.5
        if v == 0x81: return 0.25
        v = (v << 8) | self.u8()
        vd = ((v & 32768) << 16) | ((((v >> 10) & 31) + 112) << 23) | ((v & 1023) << 13)
        return struct.unpack('<f', struct.pack('<I', vd))[0]
    def f24(self):
        first = self.u8()
        if first == 0: return 0.0
        if first == 1: return 1.0
        if first == 0xff: return -1.0
        second = self.u16()
        full = (first << 23) | ((second & 32768) << 16) | ((second & 32767) << 8)
        return struct.unpack('<f', struct.pack('<I', full))[0]
    def x16(self): return self.s16() / 4096.0
    def cstr(self):
        e = self.d.index(b'\0', self.p); s = self.d[self.p:e]; self.p = e + 1
        return s.decode('latin1')

def load_names(path):
    names = {}
    if not path: return names
    src = re.sub(r'//.*', '', open(path, encoding='latin1').read())
    for i, a, b in re.findall(r'(0x[0-9a-fA-F]+)\s*,\s*(?:\(void \*\))?\s*(\w+)\s*,\s*(?:\(void \*\))?\s*(\w+)', src):
        names[int(i, 16)] = a
    return names

def parse(d):
    r = R(d)
    doc = {}
    song = r.u32(); doc['song'] = (r.p, song); r.p += (song + 3) & ~3
    samp = r.u32(); doc['samples'] = (r.p, samp); r.p += (samp + 3) & ~3
    nops = r.short(); nspl = r.short()
    classes = []
    while True:
        conv = struct.unpack_from('<I', d, r.p)[0]
        if conv == 0: break
        r.p += 4
        cid = r.u8()
        classes.append({'id': cid, 'conv': conv, 'pack': r.cstr()})
    r.p += 4
    ops = []
    for i in range(nops):
        t = r.u8()
        cls = classes[t & 0x7f]
        op = {'index': i, 'class': t & 0x7f, 'inputs': [], 'links': [], 'params': [], 'strings': [], 'splines': []}
        if t & 0x80: n = 1
        elif cls['conv'] & OPC_FLEXINPUT: n = r.u8()
        else: n = getinput(cls['conv'])
        for k in range(n):
            delta = 0 if t & 0x80 else r.short()
            op['inputs'].append(i - 1 - delta)
        ops.append(op)
    for op in ops:
        for k in range(getlink(classes[op['class']]['conv'])):
            v = r.short(); op['links'].append(v - 1 if v else None)
    for ci, cls in enumerate(classes):
        for op in ops:
            if op['class'] != ci: continue
            for ch in cls['pack']:
                c = ch.lower()
                if c == 'g': op['params'].append(r.f16())
                elif c == 'f': op['params'].append(r.f24())
                elif c == 'e': op['params'].append(r.x16())
                elif c == 'i' or c == 'c': op['params'].append(r.s32() if c == 'i' else r.u32())
                elif c == 's': op['params'].append(r.s16())
                elif c == 'b': op['params'].append(r.u8())
                elif c == 'm':
                    op['params'].append(struct.unpack_from('<I', d, r.p)[0] & 0xffffff); r.p += 3
                else: op['params'].append(None)
            for k in range(getstring(cls['conv'])): op['strings'].append(r.cstr())
            for k in range(getspline(cls['conv'])):
                v = r.u16(); op['splines'].append(v - 1 if v else None)
    kastat = {}
    for op in ops:
        start = r.p
        while True:
            j = d[r.p]
            kastat[j if j < 0x80 else j & 0xf0] = kastat.get(j if j < 0x80 else j & 0xf0, 0) + 1
            r.p += 2 if j >= 0x80 else 1 + CMDSIZE[j]
            if j == 1: break
        op['anim'] = r.p - start
        op['animcode'] = d[start:r.p].hex()
    events = []
    for k in range(r.short()):
        e = {'op': r.short(), 'start': r.s32(), 'end': r.s32(), 'velocity': r.f24(),
             'modulation': r.f24(), 'select': r.u8(),
             'scale': [r.f24() for _ in range(3)], 'rotate': [r.f24() for _ in range(3)],
             'translate': [r.f24() for _ in range(3)], 'color': r.u32(), 'spline_ignored': r.short()}
        events.append(e)
    splines = []
    for k in range(nspl):
        j = r.u8()
        sp = {'interp': j >> 3, 'channels': []}
        for c in range(j & 7):
            n = r.short()
            sp['channels'].append([(r.u8() / 255.0, r.f16()) for _ in range(n)])
        splines.append(sp)
    doc.update(classes=classes, ops=ops, events=events, splines=splines, size=r.p, kastat=kastat)
    return doc

if __name__ == '__main__':
    ap = argparse.ArgumentParser()
    ap.add_argument('file'); ap.add_argument('--ops', action='store_true')
    ap.add_argument('--oplist'); ap.add_argument('--json')
    a = ap.parse_args()
    d = open(a.file, 'rb').read()
    doc = parse(d)
    names = load_names(a.oplist)
    print(f"file {a.file}: {len(d)} bytes, document = {doc['size']} bytes")
    print(f"song: {doc['song'][1]} bytes @{doc['song'][0]:#x}  samples: {doc['samples'][1]} bytes @{doc['samples'][0]:#x}")
    print(f"{len(doc['classes'])} classes, {len(doc['ops'])} ops, {len(doc['events'])} events, {len(doc['splines'])} splines")
    print("anim opcode histogram:", {hex(k): v for k, v in sorted(doc['kastat'].items())})
    print("\nclass  id  convention  in lnk str spl data  packing          ops  name")
    for ci, c in enumerate(doc['classes']):
        n = sum(1 for o in doc['ops'] if o['class'] == ci)
        cv = c['conv']
        print(f"{ci:4d}  {c['id']:02x}  {cv:08x}  {getinput(cv):3d} {getlink(cv):3d} {getstring(cv):3d} {getspline(cv):3d} {getdata(cv):4d}  {c['pack']:<16s} {n:4d}  {names.get(c['id'], '?')}")
    if a.ops:
        for o in doc['ops']:
            c = doc['classes'][o['class']]
            print(f"op{o['index']:04d} {names.get(c['id'], hex(c['id'])):<24s} in={o['inputs']} links={o['links']} p={o['params']} s={o['strings']}")
    if a.json:
        json.dump(doc, open(a.json, 'w'), indent=0)
