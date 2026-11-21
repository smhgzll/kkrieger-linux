#!/usr/bin/env python3
"""
Rebuild a clean, loadable PE32 from the kkrunpack memory dump so that
Ghidra / IDA / r2 see the *original* program layout:

  ImageBase 0x800000 (what the original linker used)
  .text   0x801000-0x81f000  RX
  .rdata  0x81f000-0x821000  R   (starts with the IAT)
  .data   0x821000-0x1547000 RW  (initialised part + BSS)
  .idata  appended            R   (rebuilt import directory)

usage: rebuild_pe.py image.bin imports.txt info.txt out.exe
"""
import struct, sys

img_path, imp_path, info_path, out_path = sys.argv[1:5]
img = bytearray(open(img_path, 'rb').read())
info = dict(l.split() for l in open(info_path))
DUMP_BASE = int(info['image_base'], 16)
OEP = int(info['oep'], 16)

BASE = 0x800000
SECTS = [  # name, va, vsize, characteristics
    (b'.text',  0x801000, 0x01e000, 0x60000020),   # code | exec | read
    (b'.rdata', 0x81f000, 0x002000, 0x40000040),   # init data | read
    (b'.data',  0x821000, DUMP_BASE + len(img) - 0x821000, 0xC0000040),  # + write
]
IAT_LO, IAT_HI = 0x81f000, 0x81f100

def chunk(va, n):
    o = va - DUMP_BASE
    return bytes(img[o:o + n])

# --- imports: keep only real IAT slots (others are data coincidences)
slots = []
for line in open(imp_path):
    a, dll, fn = line.split()
    a = int(a, 16)
    if IAT_LO <= a < IAT_HI:
        slots.append((a, dll, fn))
slots.sort()
groups = []  # [dll, first_slot_va, [names]]
for a, dll, fn in slots:
    if groups and groups[-1][0] == dll and groups[-1][1] + 4 * len(groups[-1][2]) == a:
        groups[-1][2].append(fn)
    else:
        groups.append([dll, a, [fn]])

IDATA_VA = (DUMP_BASE + len(img) + 0xfff) & ~0xfff
idata = bytearray()
desc_size = 20 * (len(groups) + 1)
idata += b'\0' * desc_size
patches = {}   # iat va -> hint/name rva
descs = []
for dll, first, names in groups:
    int_rva = IDATA_VA - BASE + len(idata)
    hn_rvas = []
    # INT array placeholder
    int_off = len(idata)
    idata += b'\0' * (4 * (len(names) + 1))
    for fn in names:
        hn_rvas.append(IDATA_VA - BASE + len(idata))
        idata += struct.pack('<H', 0) + fn.encode() + b'\0'
        if len(idata) & 1: idata += b'\0'
    for k, r in enumerate(hn_rvas):
        struct.pack_into('<I', idata, int_off + 4 * k, r)
        patches[first + 4 * k] = r
    name_rva = IDATA_VA - BASE + len(idata)
    idata += dll.lower().encode() + b'\0'
    descs.append((int_rva, name_rva, first - BASE))
for i, (int_rva, name_rva, iat_rva) in enumerate(descs):
    struct.pack_into('<5I', idata, 20 * i, int_rva, 0, 0, name_rva, iat_rva)
while len(idata) % 0x200: idata += b'\0'

for va, r in patches.items():
    o = va - DUMP_BASE
    img[o:o + 4] = struct.pack('<I', r)

# --- write PE
FA = 0x200
hdr = bytearray(0x400)
hdr[0:2] = b'MZ'
struct.pack_into('<I', hdr, 0x3c, 0x80)
pe = 0x80
nsec = len(SECTS) + 1
hdr[pe:pe + 4] = b'PE\0\0'
struct.pack_into('<HHIIIHH', hdr, pe + 4, 0x14c, nsec, 0x407A9A6F, 0, 0, 0xE0, 0x010F)
opt = pe + 24
size_image = IDATA_VA - BASE + len(idata)
size_image = (size_image + 0xfff) & ~0xfff
struct.pack_into('<HBBIIIIIIIIIHHHHHHIIIIHHIIII', hdr, opt,
                 0x10b, 7, 10, 0x1e000, 0, 0, OEP - BASE, 0x1000, 0x1f000,
                 BASE, 0x1000, FA, 4, 0, 0, 0, 4, 0, 0, size_image, 0x400, 0,
                 2, 0, 0x100000, 0x1000, 0x100000, 0x1000)
struct.pack_into('<II', hdr, opt + 88, 0, 16)  # LoaderFlags, NumberOfRvaAndSizes
dd = opt + 96
struct.pack_into('<II', hdr, dd + 8, IDATA_VA - BASE, desc_size)       # import dir
struct.pack_into('<II', hdr, dd + 12 * 8, IAT_LO - BASE, 0xc0)          # IAT dir

raw = bytearray()
off = 0x400
sh = opt + 0xE0
for i, (name, va, vs, ch) in enumerate(SECTS):
    data = chunk(va, vs).rstrip(b'\0')
    rs = (len(data) + FA - 1) & ~(FA - 1)
    struct.pack_into('<8sIIIIIIHHI', hdr, sh + 40 * i, name, vs, va - BASE, rs, off, 0, 0, 0, 0, ch)
    raw += data + b'\0' * (rs - len(data))
    off += rs
struct.pack_into('<8sIIIIIIHHI', hdr, sh + 40 * len(SECTS), b'.idata', len(idata),
                 IDATA_VA - BASE, len(idata), off, 0, 0, 0, 0, 0x40000040)
raw += idata
open(out_path, 'wb').write(bytes(hdr) + raw)
print(f"wrote {out_path}: {len(hdr)+len(raw)} bytes, entry {OEP:#x}, {len(slots)} imports in {len(groups)} dlls")
for dll, first, names in groups:
    print(f"  {dll:14s} @{first:#x}: {', '.join(names)}")
