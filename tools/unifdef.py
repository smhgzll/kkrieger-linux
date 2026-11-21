#!/usr/bin/env python3
"""
Minimal 'unifdef' with three-valued logic.

Removes #if/#elif/#else branches whose condition is decidable from a fixed
set of configuration macros (the kkrieger player build), keeps everything
else untouched. Conditions that mention unknown macros are only resolved when
short-circuiting makes the unknown part irrelevant (e.g. 'sINTRO && FOO' with
sINTRO=0).

usage: unifdef.py config.txt in_file out_file
config.txt lines: NAME=VALUE   (VALUE int)   or   !NAME  (known undefined)
"""
import re, sys

UNK = object()

def load_cfg(path):
    cfg = {}
    for line in open(path):
        line = line.split('#')[0].strip()
        if not line:
            continue
        if line.startswith('!'):
            cfg[line[1:]] = None          # known to be undefined
        else:
            k, v = line.split('=')
            cfg[k.strip()] = int(v, 0)
    return cfg

TOK = re.compile(r'\s*(defined|\d+[uUlL]*|0x[0-9a-fA-F]+|[A-Za-z_]\w*|&&|\|\||==|!=|<=|>=|[!()<>+\-*/])')

class Parser:
    def __init__(self, s, cfg):
        s = re.sub(r'//.*', '', s)
        s = re.sub(r'/\*.*?\*/', '', s)
        self.toks = []
        pos = 0
        s = s.strip()
        while pos < len(s):
            m = TOK.match(s, pos)
            if not m:
                raise ValueError('bad token in %r' % s)
            self.toks.append(m.group(1))
            pos = m.end()
            while pos < len(s) and s[pos].isspace():
                pos += 1
        self.i = 0
        self.cfg = cfg

    def peek(self):
        return self.toks[self.i] if self.i < len(self.toks) else None

    def take(self):
        t = self.toks[self.i]; self.i += 1; return t

    def parse(self):
        v = self.orx()
        if self.peek() is not None:
            raise ValueError('trailing')
        return v

    def orx(self):
        v = self.andx()
        while self.peek() == '||':
            self.take(); w = self.andx()
            if v is UNK or w is UNK:
                v = 1 if (v not in (UNK, 0) or w not in (UNK, 0)) else UNK
            else:
                v = 1 if (v or w) else 0
        return v

    def andx(self):
        v = self.cmp()
        while self.peek() == '&&':
            self.take(); w = self.cmp()
            if v is UNK or w is UNK:
                v = 0 if (v == 0 or w == 0) else UNK
            else:
                v = 1 if (v and w) else 0
        return v

    def cmp(self):
        v = self.add()
        while self.peek() in ('==', '!=', '<', '>', '<=', '>='):
            op = self.take(); w = self.add()
            if v is UNK or w is UNK:
                v = UNK
            else:
                v = int({'==': v == w, '!=': v != w, '<': v < w, '>': v > w,
                         '<=': v <= w, '>=': v >= w}[op])
        return v

    def add(self):
        v = self.unary()
        while self.peek() in ('+', '-', '*', '/'):
            op = self.take(); w = self.unary()
            if v is UNK or w is UNK:
                v = UNK
            else:
                v = {'+': v + w, '-': v - w, '*': v * w, '/': (v // w) if w else 0}[op]
        return v

    def unary(self):
        t = self.peek()
        if t == '!':
            self.take(); v = self.unary()
            return UNK if v is UNK else int(not v)
        if t == '-':
            self.take(); v = self.unary()
            return UNK if v is UNK else -v
        return self.prim()

    def prim(self):
        t = self.take()
        if t == '(':
            v = self.orx()
            assert self.take() == ')'
            return v
        if t == 'defined':
            paren = self.peek() == '('
            if paren: self.take()
            name = self.take()
            if paren: assert self.take() == ')'
            if name not in self.cfg:
                return UNK
            return 0 if self.cfg[name] is None else 1
        if re.match(r'\d', t):
            return int(re.sub(r'[uUlL]+$', '', t), 0)
        if t in self.cfg:
            return 0 if self.cfg[t] is None else self.cfg[t]
        return UNK

def evaluate(expr, cfg):
    try:
        return Parser(expr, cfg).parse()
    except Exception:
        return UNK

DIRECTIVE = re.compile(r'^\s*#\s*(if|ifdef|ifndef|elif|else|endif)\b(.*)$')

def process(lines, cfg):
    out = []
    # stack entries: dict(mode, taken, keep_directives)
    # mode: 'keep' (branch active, directive kept), 'emit' (branch active,
    # directives dropped), 'skip' (branch dropped)
    stack = []

    def active():
        return all(s['cur'] != 'skip' for s in stack)

    i = 0
    while i < len(lines):
        line = lines[i]
        # join continuation lines for directives
        m = DIRECTIVE.match(line)
        if m:
            full = line
            while full.rstrip('\n').endswith('\\') and i + 1 < len(lines):
                i += 1
                full = full.rstrip('\n')[:-1] + ' ' + lines[i]
            m = DIRECTIVE.match(full)
            d, rest = m.group(1), m.group(2).strip()
            if d in ('if', 'ifdef', 'ifndef'):
                if d == 'if':
                    v = evaluate(rest, cfg)
                elif d == 'ifdef':
                    v = evaluate('defined(%s)' % rest.split()[0], cfg)
                else:
                    v = evaluate('!defined(%s)' % rest.split()[0], cfg)
                if v is UNK:
                    st = {'kept': True, 'cur': 'keep', 'done': False}
                    if active(): out.append(full)
                else:
                    st = {'kept': False, 'cur': 'emit' if v else 'skip', 'done': bool(v)}
                stack.append(st)
            elif d == 'elif':
                st = stack[-1]
                if st['done']:
                    st['cur'] = 'skip'
                else:
                    v = evaluate(rest, cfg)
                    if st['kept']:
                        # previous branches unknown: keep this one as-is
                        if v == 0:
                            st['cur'] = 'skip'
                        else:
                            st['cur'] = 'keep'
                            stack.pop()
                            if active(): out.append(full)
                            stack.append(st)
                            if v not in (UNK, 0):
                                st['done'] = True
                    else:
                        if v is UNK:
                            # becomes the opening #if of a kept chain
                            st['kept'] = True
                            st['cur'] = 'keep'
                            stack.pop()
                            if active(): out.append(re.sub(r'#\s*elif', '#if', full, 1))
                            stack.append(st)
                        elif v:
                            st['cur'] = 'emit'; st['done'] = True
                        else:
                            st['cur'] = 'skip'
            elif d == 'else':
                st = stack[-1]
                if st['done']:
                    st['cur'] = 'skip'
                elif st['kept']:
                    st['cur'] = 'keep'
                    stack.pop()
                    if active(): out.append(full)
                    stack.append(st)
                else:
                    st['cur'] = 'emit'; st['done'] = True
            elif d == 'endif':
                st = stack.pop()
                if st['kept'] and active():
                    out.append(full)
            i += 1
            continue
        if active():
            out.append(line)
        i += 1
    return out

if __name__ == '__main__':
    cfg = load_cfg(sys.argv[1])
    lines = open(sys.argv[2], encoding='latin1').readlines()
    res = process(lines, cfg)
    # collapse runs of >2 blank lines left behind
    final, blank = [], 0
    for l in res:
        if l.strip() == '':
            blank += 1
            if blank > 2: continue
        else:
            blank = 0
        final.append(l)
    open(sys.argv[3], 'w', encoding='latin1').writelines(final)
