#!/usr/bin/env python3

DIRS = { "L": (-1, 0), "R": (1, 0), "U": (0, -1), "D": (0, 1) }
for l in (2, 10):
    knots = [[0, 0] for _ in range(l)]
    pos = set()
    pos.add((0, 0))
    for line in open("input.txt").readlines():
        direction, num = line.split()
        num = int(num)
        knots[0][0] += num * DIRS[direction][0]
        knots[0][1] += num * DIRS[direction][1]
        while True:
            for i in range(1, len(knots)):
                xdist, ydist = knots[i-1][0] - knots[i][0], knots[i-1][1] - knots[i][1]
                if abs(xdist) < 2 and abs(ydist) < 2:
                    break
                if abs(xdist) > 0:
                    knots[i][0] = knots[i][0] + 1 if xdist > 0 else knots[i][0] - 1
                if abs(ydist) > 0:
                    knots[i][1] = knots[i][1] + 1 if ydist > 0 else knots[i][1] - 1
            else:
                pos.add((knots[-1][0], knots[-1][1]))
                continue
            break
    print(len(pos))

