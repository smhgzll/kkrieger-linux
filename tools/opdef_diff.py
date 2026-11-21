#!/usr/bin/env python3
"""Diff op class definitions: 2004 export data (.kx) vs repo werkops.cpp"""
import re, sys
sys.path.insert(0, 'tools'); import kxdump
src = open('reference/fr_public/werkkzeug3_kkrieger/werkops.cpp', encoding='latin1').read()
src = re.sub(r'//[^\n]*', '', src)
src = re.sub(r'"\s*"', '', src)   # join "abc" "def" literals
rows = {}
for m in re.finditer(r'\{\s*"([^"]*)"\s*,\s*(0x[0-9a-fA-F]+)\s*,\s*(\w+)\s*,\s*([^,]+?)\s*,\s*([^,]+?)\s*,\s*(0x[0-9a-fA-F]+)\s*,[^,]*,[^,]*,\s*"([^"]*)"\s*,\s*(\w+)\s*,\s*(\w+)\s*,\s*(\w+)', src):
    rows[int(m.group(2), 16)] = dict(name=m.group(1), kc=m.group(3), conv=int(m.group(6), 16), pack=m.group(7), init=m.group(9), exec_=m.group(10))
doc = kxdump.parse(open(sys.argv[1], 'rb').read())
same = 0
for c in doc['classes']:
    r = rows.get(c['id'])
    if not r:
        print(f"{c['id']:02x}  NOT IN REPO              2004 conv={c['conv']:08x} pack={c['pack']}"); continue
    pk_old = c['pack'].lower().replace('g', 'e').replace('f', 'e')    # storage precision only
    pk_new = r['pack'].lower().replace('g', 'e').replace('f', 'e')
    if (r['conv'] | 0x80000000) == (c['conv'] | 0x80000000) and pk_old == pk_new:
        same += 1; continue
    flags = []
    if (r['conv'] ^ c['conv']) & 0xff: flags.append(f"data {c['conv']&0xff}->{r['conv']&0xff}")
    if (r['conv'] ^ c['conv']) & 0xfff00: flags.append(f"in/lnk/str/spl {c['conv']>>8&0xfff:03x}->{r['conv']>>8&0xfff:03x}")
    if (r['conv'] ^ c['conv']) & 0x7f000000: flags.append(f"flags {c['conv']>>24:02x}->{r['conv']>>24:02x}")
    if pk_old != pk_new: flags.append("packing")
    print(f"{c['id']:02x}  {r['name']:<14s} {r['init']:<26s} 2004 {c['conv']:08x} {c['pack']:<22s} repo {r['conv']:08x} {r['pack']:<22s} {'; '.join(flags)}")
print(f"{same} classes identical (conv + packing up to float precision)")
