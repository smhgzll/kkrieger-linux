#!/usr/bin/env python3
"""Append a code section to pno0001_unpacked.exe and redirect the Present
call in sSystem_::Render to it (frame dumper, see framedump.asm).

usage: patch_pe.py in.exe hook.bin hookva out.exe [--startgame] [--nomouse]
  --nomouse     ignore mouse movement (fixed view, see below)
  --startgame   start in game state 0 (skip intro/menu): Game::Init stores
                Switches[KGS_GAME]=8 at 0x81c019 ("mov byte [esi+0x14fe9],8")
"""
import struct, sys

src, hookbin, hookva, out = sys.argv[1], sys.argv[2], int(sys.argv[3], 0), sys.argv[4]
d = bytearray(open(src, 'rb').read())
code = open(hookbin, 'rb').read()

pe = struct.unpack_from('<I', d, 0x3c)[0]
nsec = struct.unpack_from('<H', d, pe + 6)[0]
optsz = struct.unpack_from('<H', d, pe + 20)[0]
opt = pe + 24
base = struct.unpack_from('<I', d, opt + 28)[0]
sh = opt + optsz
secs = [struct.unpack_from('<8sIIIIIIHHI', d, sh + 40 * i) for i in range(nsec)]

def va2off(va):
    rva = va - base
    for name, vs, vaddr, rs, ro, *_ in secs:
        if vaddr <= rva < vaddr + rs:
            return ro + rva - vaddr
    raise ValueError(hex(va))

# new section header
assert sh + 40 * (nsec + 1) <= secs[0][4], 'no room for another section header'
raw_off = (len(d) + 0x1ff) & ~0x1ff
d += b'\0' * (raw_off - len(d))
rawsize = (len(code) + 0x1ff) & ~0x1ff
struct.pack_into('<8sIIIIIIHHI', d, sh + 40 * nsec, b'.hook', len(code), hookva - base,
                 rawsize, raw_off, 0, 0, 0, 0, 0xE0000020)
d += code + b'\0' * (rawsize - len(code))
struct.pack_into('<H', d, pe + 6, nsec + 1)
size_image = (hookva - base + len(code) + 0xfff) & ~0xfff
struct.pack_into('<I', d, opt + 56, max(size_image, struct.unpack_from('<I', d, opt + 56)[0]))

# redirect Present: 0x804400: 53 53 53 53 50 ff 51 44 -> call hook; nop x3
site = 0x804400
o = va2off(site)
assert d[o:o + 8] == bytes.fromhex('5353535350ff5144'), d[o:o + 8].hex()
rel = hookva - (site + 5)
d[o:o + 8] = b'\xe8' + struct.pack('<i', rel) + b'\x90\x90\x90'

if '--nomouse' in sys.argv:
    # mouse look polls GetCursorPos()-(400,300) and recenters with SetCursorPos;
    # under XWayland the warp fails and the view drifts. Replace the body of
    # the poll function (0x801bae) with "report the unchanged accumulators".
    site = 0x801bae
    o = va2off(site)
    assert d[o:o + 3] == bytes.fromhex('558bec'), d[o:o + 3].hex()
    d[o:o + 23] = bytes.fromhex('8b542408' 'a1dcf88300' '894204' 'a1d8f88300' '894208' 'c20800')

if '--startgame' in sys.argv:
    o = va2off(0x81c019)
    assert d[o:o + 7] == bytes.fromhex('c686e94f010008'), d[o:o + 7].hex()
    d[o + 6] = 0

open(out, 'wb').write(d)
print('wrote', out)
