import re


DX = {"R": 1, "L": -1, "U": 0, "D": 0}
DY = {"R": 0, "L": 0, "U": -1, "D": 1}


grid_in, instructions = open("../inputs/22.txt").read().split("\n\n")
grid = {}
for y, l in enumerate(grid_in.split("\n")):
    for x, c in enumerate(l):
        if c != ' ':
            assert c == '.' or c == '#', c
            grid[(y,x)] = c

y, x, d = 0, 50, "R"

def wrap(new_p, d):
    y, x = new_p
    match y // 50, x // 50, d:
        # 1 -> 6 up
        case -1, 1, "U": return x+100, 0, "R" # check
        # 1 -> 4 left
        case  0, 0, "L": return 149-y, 0, "R" # check
        # 2 -> 6 up
        case -1, 2, "U": return 199, x-100, "U" # check
        # 2 -> 3 down
        case 1, 2, "D": return x-50, 99, "L"
        # 2 -> 5  # right
        case 0, 3, "R": return 149-y, 99, "L" # check
        # 3 -> 2  # right
        case 1, 2, "R": return 49, y+50, "U" # check
        # 3 -> 4  # left
        case 1, 0, "L": return 100, y-50, "D" # check
        # 4 -> 3  # up
        case 1, 0, "U": return x+50, 50, "R" # check
        # 4 -> 1  # left
        case 2, -1, "L": return 149-y, 50, "R" # check
        # 5 -> 2 # right
        case 2, 2, "R": return 149-y, 149, "L" # check
        # 5 -> 6  # down
        case 3, 1, "D": return x+100, 49, "L"
        # 6 -> 1  # left
        case 3, -1, "L": return 0, y-100, "D" # check
        # 6 -> 5  # right
        case 3, 1, "R": return 149, y-100, "U" # check
        # 6 -> 2  # down
        case 4, 0, "D": return 0, x+100, "D" # check

        case _, _, _: assert False, f"y={y} x={x} d={d}"


for instruction in re.findall(r"\d+|[RL]", instructions):
    match instruction:
        case "L":
            match d:
                case "R": d = "U"
                case "U": d = "L"
                case "L": d = "D"
                case "D": d = "R"
        case "R":
            match d:
                case "R": d = "D"
                case "D": d = "L"
                case "L": d = "U"
                case "U": d = "R"
        case _:
            for _ in range(int(instruction)):
                new_p = (y + DY[d], x + DX[d])
                new_d = d
                if new_p not in grid:
                    ny, nx, new_d = wrap(new_p, d)
                    new_p = (ny, nx)
                assert new_p in grid, f"{ny}, {nx}, {new_d} not in grid ({y}, {x}, {d})"
                if grid[new_p] == "#":
                    break
                elif grid[new_p] == ".":
                    y, x = new_p
                    d = new_d
                else:
                    assert False

dir_score = "RDLU".index(d)
print(dir_score + 1000 * (y+1) + 4 * (x+1))
