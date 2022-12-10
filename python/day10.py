#!/usr/bin/env python3.11

class VM:
    def __init__(self, instructions):
        self.x = self._x = 1
        self.cycle = self.cycles_left = 0
        self.instructions = instructions

    def step(self):
        self.cycle += 1
        if self.cycles_left:
            self.cycles_left -= 1
        else:
            self.x = self._x
            match next(self.instructions, ("eof")).split():
                case ["noop"]: pass
                case ["addx", num]:
                    self._x += int(num)
                    self.cycles_left = 1
                case ["eof"]: return False
        return True


vm = VM(l.strip() for l in open("../inputs/10.txt").readlines())
p1 = 0
p2 = [['.'] * 40 for _ in range(6)]
while vm.step():
    p1 += vm.cycle * vm.x if vm.cycle in (20, 60, 100, 140, 180, 220)  else 0
    y, x = (vm.cycle - 1) // 40, (vm.cycle - 1) % 40
    p2[y][x] = '#' if x in range(vm.x - 1, vm.x + 2) else ' '

print(p1)
print('\n'.join(''.join(r) for r in p2))