#!/usr/bin/env python3.11


def from_snafu(n):
    CM = {"2": 2, "1": 1, "0": 0, "-": -1, "=": -2}
    return sum(5**i * CM[c] for i, c in enumerate(reversed(n)))

def to_snafu(d):
    if d == 0:
        return "0"
    s = ""
    while d > 0:
        r = d % 5
        match r:
            case 4: s = "-" + s; r = -1
            case 3: s = "=" + s; r = -2
            case _: s = str(r) + s
        d = (d - r) // 5
    return s


print(to_snafu(sum(from_snafu(l.strip()) for l in open("../inputs/25.txt").readlines())))