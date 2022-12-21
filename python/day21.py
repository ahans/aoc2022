#!/usr/bin/env python

from sympy import sympify, solveset


def bld(v, donts={}):
    if v in donts: return v
    if len(ds[v]) == 1:
        return ds[v][0]
    return f"({bld(ds[v][0], donts)} {ds[v][1]} {bld(ds[v][2], donts)})"

ds = {l[0] : l[1].split() for l in [l.split(": ") for l in open("../inputs/21.txt").readlines()]}
print(sympify(bld("root")))
expr = sympify(f"{bld(ds['root'][0], {'humn'})} - {bld(ds['root'][2], {'humn'})}")
print(list(solveset(expr, expr.free_symbols.pop()))[0])