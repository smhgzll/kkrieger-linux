#!/usr/bin/env python3
"""shaderpack.py SHADERDIR OUT_SHADERS.inc OUT_MATERIALS.inc [glslc]

Compiles the GLSL shaders of port/src/shaders with glslc and packs them for
the executable:

* SPIR-V modules, with their ids renumbered the same way in every module:
  types, constants and interface variables get one id for all modules
  (keyed by their definition and decorations), and the type section is put
  in that order. The modules stay plain SPIR-V, but the many identical
  declarations become identical bytes, which the executable packer
  compresses away (8.4 KB -> 4.8 KB with xz for the game's 62 shaders).
* the material table from materials.txt: hash of the material key ->
  vertex/pixel shader index (see MaterialShaderKey() in material11.cpp).

Shader order: mat_vs*.vert, then mat_ps*.frag, sorted by name."""
import glob, os, re, struct, subprocess, sys

SRC, OUT_SHADERS, OUT_MATERIALS = sys.argv[1:4]
GLSLC = sys.argv[4] if len(sys.argv) > 4 else 'glslc'

# operand kinds per opcode: flags T = result type, R = result id; pattern of
# the remaining operands: i = id, l = literal, s = string, *x = repeat x
OPS = {
    17: ('', 'l'), 11: ('R', 's'), 14: ('', 'll'), 15: ('', 'lis*i'), 16: ('', 'i*l'),
    71: ('', 'il*l'), 72: ('', 'ill*l'),
    19: ('R', ''), 20: ('R', ''), 21: ('R', 'll'), 22: ('R', 'l'), 23: ('R', 'il'),
    25: ('R', 'illllll*l'), 27: ('R', 'i'), 28: ('R', 'ii'), 30: ('R', '*i'),
    32: ('R', 'li'), 33: ('R', '*i'),
    1: ('TR', ''), 41: ('TR', ''), 42: ('TR', ''), 43: ('TR', '*l'), 44: ('TR', '*i'), 46: ('TR', ''),
    59: ('TR', 'l*i'), 54: ('TR', 'li'), 55: ('TR', ''), 248: ('R', ''),
    61: ('TR', 'i*l'), 62: ('', 'ii*l'), 65: ('TR', 'i*i'),
    79: ('TR', 'ii*l'), 80: ('TR', '*i'), 81: ('TR', 'i*l'), 82: ('TR', 'ii*l'),
    87: ('TR', 'ii*l'), 12: ('TR', 'il*i'),
    127: ('TR', 'i'), 129: ('TR', 'ii'), 131: ('TR', 'ii'), 133: ('TR', 'ii'),
    136: ('TR', 'ii'), 141: ('TR', 'ii'), 142: ('TR', 'ii'), 148: ('TR', 'ii'),
    168: ('TR', 'i'), 169: ('TR', 'iii'),
    **{op: ('TR', 'ii') for op in range(180, 192)},          # float compares
    245: ('TR', '*i'), 246: ('', 'iil'), 247: ('', 'il'), 249: ('', 'i'),
    250: ('', 'iii*l'), 252: ('', ''), 253: ('', ''), 254: ('', 'i'), 56: ('', ''),
}
DECL = {11, 19, 20, 21, 22, 23, 25, 27, 28, 30, 32, 33, 1, 41, 42, 43, 44, 46, 59}
TYPES = DECL - {11}

def parse(words):
    """instructions of a module: [opcode, [operands], [kinds]]"""
    out, i = [], 5
    while i < len(words):
        n, op = words[i] >> 16, words[i] & 0xffff
        ops = list(words[i + 1:i + n])
        if op not in OPS:
            sys.exit('shaderpack: unknown SPIR-V opcode %d, add it to OPS' % op)
        flags, pat = OPS[op]
        kinds = (['i'] if 'T' in flags else []) + (['r'] if 'R' in flags else [])
        rest = 'l'
        while pat:
            if pat[0] == '*': rest = pat[1]; break
            kinds.append(pat[0]); pat = pat[1:]
        k, j = [], 0
        for kind in kinds:
            if j >= len(ops): break
            if kind == 's':                      # nul terminated string
                while True:
                    k.append('l'); j += 1
                    if any(((ops[j - 1] >> (8 * b)) & 255) == 0 for b in range(4)): break
            else:
                k.append(kind); j += 1
        k += [rest] * (len(ops) - j)
        out.append([op, ops, k])
        i += n
    return out

def result(ins):
    return [x for x, k in zip(ins[1], ins[2]) if k == 'r'][0]

# ---- compile
files = sorted(glob.glob(os.path.join(SRC, 'mat_vs*.vert'))) + sorted(glob.glob(os.path.join(SRC, 'mat_ps*.frag')))
modules, consts = [], []
for f in files:
    spv = subprocess.run([GLSLC, '-O', '--target-env=vulkan1.0', '-o', '-', f],
                         check=True, stdout=subprocess.PIPE).stdout
    modules.append(parse(struct.unpack('<%dI' % (len(spv) // 4), spv)))
    m = re.search(r'uniform\s+\w+\s*\{\s*vec4\s+c\[(\d+)\]', open(f).read())
    consts.append(int(m.group(1)) if m else 0)

# ---- shared ids for declarations (content + decorations), local ids after them
shared = {}
maps = []
for prog in modules:
    deco = {}
    for op, ops, k in prog:
        if op in (71, 72):
            deco.setdefault(ops[0], []).append(tuple(ops[1:]) if op == 71 else (-1,) + tuple(ops[1:]))
    ids = {}
    for ins in prog:
        if ins[0] in DECL:
            op, ops, k = ins
            key = (op,) + tuple(ids.get(x, ('?', x)) if kind == 'i' else (None if kind == 'r' else x)
                                for x, kind in zip(ops, k))
            key += tuple(sorted(deco.get(result(ins), [])))
            ids[result(ins)] = shared.setdefault(key, len(shared) + 1)
    maps.append(ids)

code, sizes = [], []
for prog, ids in zip(modules, maps):
    local = {}
    def remap(x):
        if x in ids: return ids[x]
        return local.setdefault(x, len(shared) + 1 + len(local))
    prog = [[op, [remap(x) if kind in 'ir' else x for x, kind in zip(ops, k)], k] for op, ops, k in prog]
    head = [i for i in prog if i[0] in (17, 11, 14)]
    entry = [i for i in prog if i[0] in (15, 16)]
    decos = sorted([i for i in prog if i[0] in (71, 72)], key=lambda i: i[1])
    decl = sorted([i for i in prog if i[0] in TYPES], key=result)
    body = [i for i in prog if i[0] not in (17, 11, 14, 15, 16, 71, 72) and i[0] not in TYPES]
    words = [0x07230203, 0x00010000, 0, len(shared) + len(local) + 1, 0]
    for op, ops, k in head + entry + decos + decl + body:
        words += [((len(ops) + 1) << 16) | op] + ops
    code += words
    sizes.append(len(words))
    if os.environ.get('SHADERPACK_DUMP'):            # for spirv-val
        with open(os.path.join(os.environ['SHADERPACK_DUMP'], '%02d.spv' % len(sizes)), 'wb') as f:
            f.write(struct.pack('<%dI' % len(words), *words))

# ---- material table
keys = []
for line in open(os.path.join(SRC, 'materials.txt')):
    line = line.split('#')[0].split()
    if not line: continue
    fields = [int(x, 16) for x in line[:-2]]
    vs, ps = int(line[-2]), int(line[-1])
    h = 2166136261                       # FNV-1a over the key words
    for w in fields:
        h = ((h ^ w) * 16777619) & 0xffffffff
    keys.append((h, vs, ps))
nvs = len(glob.glob(os.path.join(SRC, 'mat_vs*.vert')))
assert len(set(h for h, vs, ps in keys)) == len(keys), 'material key hash collision'

def array(name, ctype, values, per_line=8, fmt='0x%08x'):
    lines = ['static const %s %s[%d] =' % (ctype, name, len(values)), '{']
    for i in range(0, len(values), per_line):
        lines.append('  ' + ','.join(fmt % v for v in values[i:i + per_line]) + ',')
    return '\n'.join(lines + ['};', ''])

hdr = '// generated by tools/shaderpack.py from port/src/shaders: do not edit\n\n'
with open(OUT_SHADERS, 'w') as f:
    f.write(hdr)
    f.write('#define SHADER_COUNT %d\n\n' % len(files))
    f.write('// %s\n' % ' '.join(os.path.basename(x) for x in files))
    f.write(array('ShaderWords', 'uint16_t', sizes, 16, '%d'))
    f.write(array('ShaderConsts', 'uint8_t', consts, 16, '%d'))
    f.write(array('ShaderCode', 'uint32_t', code))
with open(OUT_MATERIALS, 'w') as f:
    f.write(hdr)
    f.write('#define MATERIAL_SHADERS %d\n\n' % len(keys))
    f.write(array('MaterialShaderKey', 'sU32', [h for h, vs, ps in keys]))
    f.write(array('MaterialShaderVS', 'sU8', [vs for h, vs, ps in keys], 16, '%d'))
    f.write(array('MaterialShaderPS', 'sU8', [nvs + ps for h, vs, ps in keys], 16, '%d'))
print('shaderpack: %d shaders (%d bytes of SPIR-V), %d materials' % (len(files), 4 * len(code), len(keys)))
