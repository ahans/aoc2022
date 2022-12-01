import sys

cals = sorted([sum(map(int, elf.split("\n"))) for elf in sys.stdin.read().strip().split("\n\n")])
print(cals[-1])
print(sum(cals[-3:]))
