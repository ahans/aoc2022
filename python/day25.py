#!/usr/bin/env python3.11


def from_snafu(n):
    CM = {"2": 2, "1": 1, "0": 0, "-": -1, "=": -2}
    return sum(5**i * CM[c] for i, c in enumerate(reversed(n)))

def to_snafu(d):
    return "" if d == 0 else to_snafu((d + 2) // 5) + "012=-"[d % 5]


print(to_snafu(sum(from_snafu(l.strip()) for l in open("../inputs/25.txt").readlines())))
