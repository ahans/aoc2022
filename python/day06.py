#!/usr/bin/env python3

def solve(inp):
    sop = None
    for i in range(len(inp)):
        if not sop and len(set(inp[i:i+4])) == 4:
            sop = i + 4
        elif sop and len(set(inp[i:i+14])) == 14:
            return sop, i + 14

s = open("../inputs/06.txt").read()
print(*(next((i + n for i in range(len(s)) if len(set(s[i:i+n])) == n)) for n in (4, 14)))

