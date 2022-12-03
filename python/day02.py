#!/usr/bin/env python3

import sys

SCORES = {
    "A X": (4, 3),
    "A Y": (8, 4),
    "A Z": (3, 8),
    "B X": (1, 1),
    "B Y": (5, 5),
    "B Z": (9, 9),
    "C X": (7, 2),
    "C Y": (2, 6),
    "C Z": (6, 7),
}

lines = [l.strip() for l in sys.stdin.readlines()]
# print(*(sum(SCORES[l][p] for l in lines) for p in (0, 1)))
s0, s1 = 0, 0
for l in lines:
    ls = l.split()
    a, b = ord(ls[0]) - ord('A'), ord(ls[1]) - ord('X')
    s0 += 3 * ((b - a + 4) % 3) + b + 1
    s1 += (a + b + 2) % 3 + 3 * b + 1
print(s0, s1)
