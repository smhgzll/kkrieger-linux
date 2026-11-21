#!/usr/bin/env python3
"""packprof.py ELF MAP KKPACK [objects | symbols OBJECT.o]

Packed size profile: zeroes the sections of each object file (or of each
function/data symbol of one object) in an unstripped size build and packs
again; the size drop is what that part costs in the pack.

  cd port && make prof          # build-prof/kkrieger + build-prof/kkrieger.map
  ../tools/packprof.py build-prof/kkrieger build-prof/kkrieger.map ../tools/kkpack/kkpack
  ../tools/packprof.py ... symbols glrender.o"""
import collections, os, re, struct, subprocess, sys, tempfile

ELF, MAP, KKPACK = sys.argv[1:4]
mode = sys.argv[4] if len(sys.argv) > 4 else 'objects'
elf = open(ELF, 'rb').read()

phoff, = struct.unpack_from('<I', elf, 28)
phnum, = struct.unpack_from('<H', elf, 44)
segs = []
for i in range(phnum):
    ptype, poff, pvaddr, _, pfilesz = struct.unpack_from('<IIIII', elf, phoff + 32 * i)
    if ptype == 1: segs.append((pvaddr, poff, pfilesz))
def fileoff(va):
    for v, o, n in segs:
        if v <= va < v + n: return o + va - v
    return None

# input sections of the link map (long names wrap to the next line)
entries = set()
for m in re.finditer(r'^ (\.(?:text|rodata|data)\S*)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+)', open(MAP).read(), re.M):
    name, addr, size, obj = m.group(1), int(m.group(2), 16), int(m.group(3), 16), m.group(4)
    if size and fileoff(addr) is not None and not obj.startswith('/usr'):
        entries.add((name, addr, size, os.path.basename(obj)))

tmp = tempfile.mkdtemp()
def packed(data):
    p = os.path.join(tmp, 'e')
    open(p, 'wb').write(data); os.chmod(p, 0o755)
    out = subprocess.run([KKPACK, '-x', p, p + '.bin', p + '.inc'], capture_output=True, text=True).stdout
    return int(re.search(r'-> (\d+) packed', out).group(1))

base = packed(elf)
groups = collections.defaultdict(list)
for name, addr, size, obj in entries:
    if mode == 'objects': groups[obj].append((addr, size))
    elif obj == sys.argv[5]: groups[name].append((addr, size))
rows = []
for group, ranges in groups.items():
    raw = sum(s for a, s in ranges)
    if raw < 16: continue
    d = bytearray(elf)
    for a, s in ranges:
        o = fileoff(a); d[o:o + s] = bytes(s)
    rows.append((base - packed(bytes(d)), raw, group))
print('packed %d bytes; cost of each part (packed, raw):' % base)
for cost, raw, group in sorted(rows, reverse=True):
    print('%7d %8d  %s' % (cost, raw, group))
print('%7d          sum' % sum(r[0] for r in rows))
