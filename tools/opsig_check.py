#!/usr/bin/env python3
"""Compare the stack-word count each op class gets from the 2004 data
(convention word) with what the repo implementation's __stdcall signature
expects. Mismatches = ops whose implementation changed after 2004."""
import re, sys, glob
sys.path.insert(0, 'tools'); import kxdump
WORDS = {'sF323': 3, 'sFSRT': 9, 'sF322': 2, 'sF324': 4, 'sInt2': 2, 'sInt3': 3, 'sInt4': 4, 'sVector': 4, 'sMatrix': 16}
def sigwords(args):
    args = re.sub(r'\s+', ' ', args).strip()
    if args in ('', 'void'): return 0, []
    out = []
    for a in args.split(','):
        a = a.strip(); typ = a.split()[0] if a.split() else a
        if a.startswith('class '): typ = a.split()[1]
        w = 1 if '*' in a else WORDS.get(typ, 1)
        out.append((a, w))
    return sum(w for _, w in out), out
def expected(conv):
    if conv & 0x01000000: return None
    n = 0
    if conv & (0x40000000 | 0x20000000): n += 1
    if conv & 0x00800000: n += 1
    if conv & 0x20000000: return n          # ALTINIT: nothing else
    n += (conv >> 8) & 15
    n += (conv >> 12) & 15
    n += conv & 0xff
    n += (conv >> 16) & 7
    n += (conv >> 20) & 7
    if conv & 0x08000000: n += 1
    return n
def main(kx, oplist):
    doc = kxdump.parse(open(kx, 'rb').read())
    names = kxdump.load_names(oplist)
    sig = {}
    for f in glob.glob('port/src/*.cpp') + glob.glob('port/src/*.hpp'):
        s = open(f, encoding='latin1').read()
        for m in re.finditer(r'__stdcall\s+(\w+)\s*\(([^)]*)\)', s):
            sig.setdefault(m.group(1), m.group(2))
    ok, bad = [], []
    for c in doc['classes']:
        nm = names.get(c['id'])
        e = expected(c['conv'])
        if nm not in sig:
            bad.append((c, nm, e, None, '(no implementation in repo)')); continue
        n, parts = sigwords(sig[nm])
        (ok if e is None or e == n else bad).append((c, nm, e, n, sig[nm]))
    print(f"{len(ok)} op classes match, {len(bad)} differ")
    for c, nm, e, n, s in bad:
        print(f"  {c['id']:02x} {str(nm):<24s} conv={c['conv']:08x} 2004={e} repo={n} pack={c['pack']}\n      repo: {re.sub(r'\\s+',' ',s)[:150]}")
main(sys.argv[1], sys.argv[2])
