#!/usr/bin/env python3.10


walls = set()
for line in open("../inputs/14.txt").readlines():
    coords = line.split(" -> ")
    for a, b in zip(coords[:-1], coords[1:]):
        x0, y0 = map(int, a.split(","))
        x1, y1 = map(int, b.split(","))
        for y in range(min(y0, y1), max(y0, y1)+1):
            for x in range(min(x0, x1), max(x0, x1)+1):
                walls.add((x,y))

sand = set()

def free(x, y, bottom_y=None):
    if bottom_y and y == bottom_y:
        return False
    return not ((x,y) in walls or (x,y) in sand)


def solve(walls, part2 = False):
    fallen_out_y = None if part2 else max(y for x,y in walls) 
    bottom_y = max(y for x,y in walls) + 2 if part2 else None
    while True:
        x, y = 500, 0
        while True:
            if free(x, y + 1, bottom_y):
                y = y + 1
            elif free(x - 1, y + 1, bottom_y):
                x, y = x - 1, y + 1
            elif free(x + 1, y + 1, bottom_y):
                x, y = x + 1, y + 1
            else:
                if part2 and (x,y) in sand:
                    return len(sand)
                sand.add((x,y))
                break
            if fallen_out_y and fallen_out_y == y:
                return len(sand)
                
print(solve(walls, False))
print(solve(walls, True))