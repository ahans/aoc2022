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
p2 = ""
while vm.step():
    p1 += vm.cycle * vm.x if (vm.cycle - 20) % 40 == 0 else 0
    x = (vm.cycle - 1) % 40
    p2 += "#" if x in range(vm.x - 1, vm.x + 2) else " "
    if (x + 1) % 40 == 0:
        p2 += "\n"

print(p1)
print(p2)
