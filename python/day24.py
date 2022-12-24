import sys
import heapq
from collections import defaultdict
from frozendict import frozendict


blizzards = defaultdict(lambda: ())
lines = open("../inputs/24.txt").read().strip().splitlines()
h, w = len(lines) - 2, len(lines[0]) - 2
for y, l in enumerate(lines):
    l = l.strip()
    if not l: continue
    for x, c in enumerate(l):
        if c in "<>^v": blizzards[(y,x)] = (*blizzards[(y,x)], c)


goal = h + 1, w
start = (0,1)

def find_path(start, goal):
    def l1(a, b):
        return abs(a[0] - b[0]) + abs(a[1] - b[1])
    global blizzards
    q = [(l1(start, goal), 0, start, frozendict(blizzards))]
    visited = set()
    while q:
        estimated, cost, pos, blizzards = heapq.heappop(q)
        if (pos, blizzards) in visited:
            continue
        visited.add((pos, blizzards))
        if pos == goal:
            return cost
        if pos in blizzards and blizzards[pos]:
            continue
        # move blizzards
        new_blizzards = defaultdict(lambda: [])
        for (by, bx), blizzard_list in blizzards.items():
            for b in blizzard_list:
                match b:
                    case "<": new_p = (by, ((bx-1-1) % w) + 1)
                    case ">": new_p = (by, ((bx-1+1) % w) + 1)
                    case "^": new_p = (((by-1-1) % h) + 1, bx)
                    case "v": new_p = (((by-1+1) % h) + 1, bx)
                new_blizzards[new_p] = (*new_blizzards[new_p], b)
        y, x = pos
        blizzards = frozendict(new_blizzards)
        # iterate actions
        for ds in [(0, 0), (-1, 0), (1, 0), (0, -1), (0, 1)]:
            ny, nx = (p := (y + ds[0], x + ds[1]))
            if (ny <= 0 or ny >= h+1 or nx <= 0 or nx >= w+1) and p != goal and p != start:
                continue
            if p in blizzards:
                continue
            heapq.heappush(q,  (cost + 1 + l1(p, goal), cost + 1, p, blizzards))


print(p1 := find_path(start, goal))
print(p1 + find_path(goal, start) + find_path(start, goal))
