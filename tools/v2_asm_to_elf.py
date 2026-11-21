#!/usr/bin/env python3
"""Adapt the Win32 NASM source of the V2 synth (_viruz2a.asm) to ELF32.
 * '_name@N' (stdcall decoration) -> 'name'  (what clang emits on Linux)
 * internal helpers with generic names (pow, fastsin, ...) get a 'v2_' prefix
   so they can't collide with libm when the asm is linked into an ELF binary.
usage: v2_asm_to_elf.py in.asm out.asm"""
import re, sys
s = open(sys.argv[1], encoding='latin1').read()
s = re.sub(r'\b_(\w+)@\d+\b', r'\1', s)
for name in ['pow', 'pow2', 'fastatan', 'fastsin', 'fastsinrc', 'calcfreq', 'calcfreq2',
             'calcNewSampleRate', 'syCompRender']:
    s = re.sub(r'(?<![\w.])%s(?!\w)' % name, 'v2_' + name, s)
open(sys.argv[2], 'w', encoding='latin1').write(s)
