#!/usr/bin/env python3.10

import json


def cmp(a, b):
    match (a, b):
        case int(), int(): return b - a
        case int(), list(): return cmp([a], b)
        case list(), int(): return cmp(a, [b])
        case list(), list():
            for aa, bb in zip(a, b):
                if (r := cmp(aa, bb)) != 0:
                    return r
            return len(b) - len(a)
    assert False


p1 = 0
num_smaller = [0, 0]
for i, pair in enumerate(open("../inputs/13.txt").read().strip().split("\n\n")):
    a, b = [json.loads(s.strip()) for s in pair.split("\n")]
    if cmp(a, b) > 0:
        p1 += i + 1
    for o in (a, b):
        num_smaller[0] += 1 if cmp(o, [[2]]) > 0 else 0
        num_smaller[1] += 1 if cmp(o, [[6]]) > 0 else 0
print(p1)
print((num_smaller[0] + 1) * (num_smaller[1] + 2))
