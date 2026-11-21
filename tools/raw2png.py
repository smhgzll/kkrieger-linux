#!/usr/bin/env python3
"""raw2png.py out_dir in.raw... : 1024x768 BGRA dumps (framedump.asm) -> half size PNG"""
import struct, zlib, sys, os
out = sys.argv[1]
for f in sys.argv[2:]:
    d = open(f, 'rb').read(); w, h = 1024, 768
    rows = []
    for y in range(0, h, 2):
        r = d[y*w*4:(y+1)*w*4]; row = bytearray()
        for x in range(0, w, 2):
            b, g, rr, a = r[x*4:x*4+4]; row += bytes((rr, g, b))
        rows.append(b'\0' + bytes(row))
    def chunk(t, data): return struct.pack('>I', len(data)) + t + data + struct.pack('>I', zlib.crc32(t + data) & 0xffffffff)
    o = os.path.join(out, os.path.basename(f)[:-4] + '.png')
    open(o, 'wb').write(b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', w//2, h//2, 8, 2, 0, 0, 0)) + chunk(b'IDAT', zlib.compress(b''.join(rows), 6)) + chunk(b'IEND', b''))
