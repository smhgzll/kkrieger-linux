#!/usr/bin/env python3
"""tga2png.py in.tga [out.png] [--half]  - 32bit uncompressed top-left TGA -> PNG"""
import struct, zlib, sys
def convert(fn, out, half=False):
    d=open(fn,'rb').read(); w,h=struct.unpack_from('<HH',d,12); px=d[18:]
    step=2 if half else 1
    rows=[]
    for y in range(0,h,step):
        r=px[y*w*4:(y+1)*w*4]
        row=bytearray()
        for x in range(0,w,step):
            b,g,rr,a=r[x*4:x*4+4]; row+=bytes((rr,g,b))
        rows.append(b'\0'+bytes(row))
    W,H=(w+step-1)//step,(h+step-1)//step
    def chunk(t,data): return struct.pack('>I',len(data))+t+data+struct.pack('>I',zlib.crc32(t+data)&0xffffffff)
    open(out,'wb').write(b'\x89PNG\r\n\x1a\n'+chunk(b'IHDR',struct.pack('>IIBBBBB',W,H,8,2,0,0,0))+chunk(b'IDAT',zlib.compress(b''.join(rows),6))+chunk(b'IEND',b''))
if __name__=='__main__':
    a=[x for x in sys.argv[1:] if not x.startswith('--')]
    for f in a: convert(f, f[:-4]+'.png', '--half' in sys.argv)
