import sys
from collections import defaultdict


DIFFS = (
    (+1, 0, 0),
    (-1, 0, 0),
    (0, +1, 0),
    (0, -1, 0),
    (0, 0, +1),
    (0, 0, -1),
)

grid = set()
sides = defaultdict(int)
for line in open("../inputs/18.txt").readlines():
    x, y, z = [1 * float(x) for x in line.split(",")]
    grid.add((x,y,z))
    for (dx, dy, dz) in DIFFS:
        s = (x + 0.5*dx, y + 0.5*dy, z + 0.5*dz)
        sides[s] += 1
outsides = set(k for k,v in sides.items() if v == 1)
print(len(outsides))

mins = [sys.maxsize, sys.maxsize, sys.maxsize]
maxs = [0, 0, 0]
for x, y, z in grid:
    mins[0] = min(mins[0], x)
    mins[1] = min(mins[1], y)
    mins[2] = min(mins[2], z)
    maxs[0] = max(maxs[0], x)
    maxs[1] = max(maxs[1], y)
    maxs[2] = max(maxs[2], z)


q = [mins]
filled = set()
while q:
    x, y, z = q.pop(0)
    for (dx, dy, dz) in DIFFS:
        nx, ny, nz = (x + dx, y + dy, z + dz)
        k = (nx, ny, nz)
        if k in grid or k in filled:
            continue
        if not (mins[0]-1 <= nx <= maxs[0]+1 and mins[1]-1 <= ny <= maxs[1]+1 and mins[2]-1 <= nz <= maxs[2]+1):
            continue
        filled.add((nx,ny,nz))
        q.append(k)

flood_filled_sides = set()
for x, y, z in filled:
    for (dx, dy, dz) in DIFFS:
        s = (x + 0.5*dx, y + 0.5*dy, z + 0.5*dz)
        flood_filled_sides.add(s)
print(len(flood_filled_sides & outsides))