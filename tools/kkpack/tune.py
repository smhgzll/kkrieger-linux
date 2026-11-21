#!/usr/bin/env python3
"""tune.py KKPACK ELF [MASKS [INDEX,...]]

Searches the context masks of model.asm for one executable: coordinate
descent, every value of one mask (context bytes, then byte bits) at a time,
packs in parallel through KKPACK_MASKS (see kkpack.cpp). MASKS = 22 hex
bytes to start from (default: the ones in model.asm; 2*NMODEL bytes for a
kkpack built with another NMODEL), INDEX = only search these masks. Prints
each improvement; put the result into model.asm (masks, bitm)."""
import concurrent.futures, os, re, subprocess, sys, tempfile

KKPACK, ELF = sys.argv[1:3]
start = sys.argv[3] if len(sys.argv) > 3 else '1f2788070a090503040201' 'ffffffe0ffffffffffffff'
cur = list(bytes.fromhex(start))
n = len(cur) // 2
only = [int(i) for i in sys.argv[4].split(',')] if len(sys.argv) > 4 else range(2 * n)
tmp = tempfile.mkdtemp(dir=os.environ.get('TMPDIR'))

def packed(m):
    h = bytes(m).hex()
    p = os.path.join(tmp, h)
    out = subprocess.run([KKPACK, '-x', ELF, p + '.bin', p + '.inc'], capture_output=True, text=True,
                         env=dict(os.environ, KKPACK_MASKS=h, KKPACK_NOVERIFY='1')).stdout
    os.unlink(p + '.bin'); os.unlink(p + '.inc')
    return int(re.search(r'-> (\d+) packed', out).group(1))

pool = concurrent.futures.ThreadPoolExecutor(os.cpu_count())
best = packed(cur)
print('start %s %d' % (bytes(cur).hex(), best), flush=True)
improved = True
while improved:
    improved = False
    for i in only:
        values = [v for v in range(1, 256) if v != cur[i]]
        cands = [cur[:i] + [v] + cur[i + 1:] for v in values]
        sizes = list(pool.map(packed, cands))
        s, c = min(zip(sizes, cands))
        if s < best:
            best, cur, improved = s, c, True
            print('%-6s %s %d' % ('mask%d' % i if i < n else 'bitm%d' % (i - n), bytes(cur).hex(), best), flush=True)
print('done %s %d' % (bytes(cur).hex(), best))
