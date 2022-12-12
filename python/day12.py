#!/usr/bin/env python3.10

grid = [list(map(ord, l.strip())) for l in open("../inputs/12.txt").readlines()]
h, w = len(grid), len(grid[0])
start, end = [[(y, x) for x in range(w) for y in range(h) if grid[y][x] == c][0] for c in (ord("S"), ord("E"))]

grid[start[0]][start[1]] = ord("a")
grid[end[0]][end[1]] = ord("z")

q = [(0, end)]
seen = set()
lengths = {}
while q:
    l, p = q.pop(-1)
    if p in seen:
        continue
    seen.add(p)
    y, x = p
    if grid[y][x] == ord("a"):
        lengths[p] = l

    for dy, dx in ((1, 0), (-1, 0), (0, 1), (0, -1)):
        ny, nx = y + dy, x + dx
        if 0 <= ny < h and 0 <= nx < w and (ny, nx) not in seen and (grid[y][x] - grid[ny][nx]) <= 1:
            q.append((l + 1, (ny, nx)))

print(lengths[start])
print(min(lengths.values()))