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
print("{}\n{}".format(*[sum([SCORES[l][p] for l in lines]) for p in (0, 1)]))
