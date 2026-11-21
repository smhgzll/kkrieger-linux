#!/usr/bin/env python3
"""shotcmp.py A B: compare the KK_SHOT screenshots of two verify_small.sh runs
(percentage of pixels whose colour differs)."""
import glob, os, struct, sys

def load(f):
    d = open(f, 'rb').read()
    return d[18:]

A, B = sys.argv[1], sys.argv[2]
worst = 0.0
for sub in ['', 'game/', 'play/']:
    fa = sorted(glob.glob(os.path.join(A, sub, 'kkshot_*.tga')))
    fb = sorted(glob.glob(os.path.join(B, sub, 'kkshot_*.tga')))
    for x, y in zip(fa, fb):
        a, b = load(x), load(y)
        n = min(len(a), len(b))
        diff = sum(1 for i in range(0, n, 4) if a[i:i + 3] != b[i:i + 3])
        pct = 100.0 * diff / (n / 4)
        worst = max(worst, pct)
        print('%-26s %6.2f%% pixels differ' % (sub + os.path.basename(x), pct))
print('worst: %.2f%%' % worst)
