#!/usr/bin/env python3.11

from copy import deepcopy
from dataclasses import dataclass
from operator import __add__, __mul__


@dataclass
class Monkey:
    items: list
    op: tuple
    divisable_by: int
    to: tuple


monkeys = []
n = 1
for id, t in enumerate(open("../inputs/11.txt").read().split("\n\n")):
    lines = t.split("\n")
    items = [int(x) for x in lines[1].strip().split(":")[-1].split(",")]
    op, num = lines[2].strip().split(": ")[-1].strip().split()[-2:]
    op = (__add__ if op == "+" else __mul__, num if num == "old" else int(num))
    divisable_by, to_if_true, to_if_false = (int(s.strip().split()[-1]) for s in lines[3:6])
    n *= divisable_by
    monkeys.append(Monkey(items, op, divisable_by, (to_if_true, to_if_false)))

print(n)
for num_rounds in (20,):
    counts = [0] * len(monkeys)
    part_monkeys = deepcopy(monkeys)
    pp = (lambda x: x // 3) if num_rounds == 20 else (lambda x: x % n)
    for i in range(num_rounds):
        for monkey_id, m in enumerate(part_monkeys):
            while m.items:
                counts[monkey_id] += 1
                item = m.items.pop()
                new = pp(m.op[0](item, item if m.op[1] == "old" else m.op[1]))
                part_monkeys[m.to[new % m.divisable_by != 0]].items.append(new)

    counts.sort(reverse=True)
    print(counts[0] * counts[1])