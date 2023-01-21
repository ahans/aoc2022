#!/usr/bin/env python

# from sympy import sympify, solveset
from collections import defaultdict
import sys


grid, instructions = sys.stdin.read().split("\n\n")
grid = grid.split("\n")
h = len(grid)
w = max(len(l) for l in grid)
print(h, w)
x_limits = []
y_limits = [[99999999, 0] for _ in range(w)]
for i, g in enumerate(grid[::]):
    o1 = g.find('.')
    if o1 == -1:
        o1 = 99999
    o2 = g.find('#')
    if o2 == -1:
        o2 = 999999
    begin = min(o1, o2)
    assert begin >= 0
    x_limits.append((begin, len(g)))
    for x in range(begin, len(g)):
        y_limits[x][0] = min(i, y_limits[x][0])
        y_limits[x][1] = max(i+1, y_limits[x][1])
print("\n".join(map(str, grid)))
print(y_limits)

x, y, d = x_limits[0][0], 0, 'R'

print(x, y, d)
while instructions:
        print(f"x={x} y={y} d={d}")
        next_r = instructions.find("R")
        next_l = instructions.find("L")
        if next_r == -1: next_r = len(instructions)
        if next_l == -1: next_l = len(instructions)
        if next_r == 0 or next_l == 0:
            i = instructions[0]
            instructions = instructions[1:]
            if i == "L":
                if d == "R":
                    d = "U"
                elif d == "U":
                    d = "L"
                elif d == "L":
                    d = "D"
                elif d == "D":
                    d = "R"
                else:
                    assert False
            elif i == "R":
                if d == "R":
                    d = "D"
                elif d == "D":
                    d = "L"
                elif d == "L":
                    d = "U"
                elif d == "U":
                    d = "R"
            else:
                assert False
        else:
            n = int(instructions[:min(next_r, next_l)])
            instructions = instructions[min(next_r, next_l):]
            for _ in range(n):
                ox = x_limits[y][0]
                lx = x_limits[y][1] - ox
                # print("x",x)
                oy = y_limits[x][0]
                ly = y_limits[x][1] - oy
                if d == "R":
                    nx = ((x-ox + 1) % lx) + ox
                    ny = y
                elif d == "L":
                    nx = ((x-ox - 1) % lx) + ox
                    ny = y
                elif d == "D":
                    nx = x
                    ny = ((y-oy + 1) % ly) + oy
                elif d == "U":
                    nx = x
                    ny = ((y-oy - 1) % ly) + oy
                print(f"nx={nx} ny={ny}")
                if grid[ny][nx] != '.':
                    print("wall")
                    break
                x = nx
                y = ny
p1 = 0
if d == "R":
    p1 = 0
elif d == "D":
    p1 = 1
elif d == "L":
    p1 = 2
elif d == "U":
    p1 = 3
print(x, y)
print(1000 * (y+1) + 4 * (x+1) + p1)
