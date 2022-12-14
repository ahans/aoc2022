#include "../common.hh"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>
#include <functional>
#include <unordered_set>
#include <optional>

Result day14() {
    std::ifstream in{"../inputs/14.txt"};
    // std::ifstream in{"/home/alex/src/aoc2022/cpp/sample.txt"};
    using Point = std::pair<int, int>;
    // std::unordered_set<int64_t> walls;
    std::vector<bool> walls(512 * 1024);
    auto parse_point = [](std::string const& s, size_t& i) -> Point {
        int x;
        i += parse<int, 1, 3>(&s[i], x);
        int y;
        i++; // ,
        i += parse<int, 1, 3>(&s[i], y);
        return Point{x, y};
    };

    // constexpr auto hash = [](int x, int y) { return y << 16 | x; };
    constexpr auto index = [](int x, int y) { return x * 256 + y; };

    int floor{};
    for (std::string line; std::getline(in, line);) {
        size_t i{0};
        auto [x0, y0] = parse_point(line, i);
        floor = std::max(floor, y0);
        while (i < line.length()) {
            i += 4;
            auto [x1, y1] = parse_point(line, i);

            floor = std::max(floor, y1);
            for (auto y = std::min(y0, y1); y <= std::max(y0, y1); ++y) {
                for (auto x = std::min(x0, x1); x <= std::max(x0, x1); ++x) {
                    // walls.insert(hash(x, y));
                    walls[index(x, y)] = true;
                }
            }
            x0 = x1;
            y0 = y1;
        }
    }

    int p1{};
    int p2{};
    for (auto t = 0; p2 == 0; ++t) {
        int x = 500;
        int y = 0;
        while (true) {
            if (y + 1 < (floor + 2) && !walls[index(x, y + 1)]) {
                y = y + 1;
            } else if (y + 1 < (floor + 2) && !walls[index(x - 1, y + 1)]) {
                y = y + 1;
                x = x - 1;
            } else if (y + 1 < (floor + 2) && !walls[index(x + 1, y + 1)]) {
                y = y + 1;
                x = x + 1;
            } else {
                if (walls[index(x, y)]) {
                    p2 = t;
                    break;
                }
                walls[index(x, y)] = true;
                if (y >= floor && p1 == 0) {
                    p1 = t;
                }
                break;
            }
        }
    }

    return {std::to_string(p1), std::to_string(p2)};
}

REGISTER_FUNC_FOR_DAY(14, day14)
