#include "../common.hh"

#include <queue>
#include <string>
#include <vector>

Result day12() {
    std::ifstream in{"../inputs/12.txt"};
    std::vector<char> grid;
    int start{}, end{};
    int w{}, h{};
    for (std::string line; std::getline(in, line);) {
        if (w == 0)
            w = line.length();
        for (int i = 0; i < w; ++i) {
            auto c = line[i];
            if (c == 'S') {
                c = 'a';
                start = h * w + i;
            }
            if (c == 'E') {
                c = 'z';
                end = h * w + i;
            }
            grid.push_back(c);
        }
        ++h;
    }

    int p1{};
    int p2{};

    std::vector<bool> seen(grid.size());
    std::deque<std::pair<int, int>> q;
    q.push_back(std::make_pair(0, end));
    while (true) {
        auto const [l, cur]{q.front()};
        q.pop_front();
        if (seen[cur]) {
            continue;
        }
        seen[cur] = true;
        if (grid[cur] == 'a') {
            if (p2 == 0) {
                p2 = l;
            } else if (cur == start) {
                p1 = l;
                break;
            }
        }
        for (auto d : {1, -1, -w, w}) {
            auto const next{cur + d};
            if (next < 0 || next > static_cast<int>(grid.size()) || seen[next] || (grid[cur] - grid[next]) > 1) {
                continue;
            }
            q.push_back({l + 1, next});
        }
    }

    return {std::to_string(p1), std::to_string(p2)};
}

REGISTER_FUNC_FOR_DAY(12, day12)
