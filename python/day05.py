#!/usr/bin/env python3

def solve(inp, part2 = False):
    stacks, instructions = inp.split("\n\n")
    levels = [l[1::4] for l in stacks.split("\n")]
    stacks = [list(reversed(list(filter(lambda y: y.isalpha(), x)))) for x in zip(*levels)]

    for ins in instructions.strip().split("\n"):
        num, stack_from, stack_to = (a + b for a, b in zip(map(int, ins.strip().split()[1::2]), (0, -1, -1)))
        new = stacks[stack_from][-num:]
        stacks[stack_to].extend(reversed(new) if part2 else new)
        stacks[stack_from] = stacks[stack_from][:-num]

    return "".join(s[-1] for s in stacks)


inp = open("../inputs/05.txt").read()
print(solve(inp))
print(solve(inp, True))