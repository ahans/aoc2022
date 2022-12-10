#include "../common.hh"

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <chrono>

Result day08() {
    std::ifstream in{"../inputs/08.txt"};
    std::array<std::array<char, 99>, 99> grid{};
    constexpr auto width = 99;
    constexpr auto height = 99;
    auto i{0};
    for (std::string line; std::getline(in, line);) {
        std::transform(line.begin(), line.end(), grid[i++].begin(), [](char c) { return c - '0'; });
    }

    int p1{}, p2{};
    for (auto y{0}; y < height; ++y) {
        for (auto x{0}; x < width; ++x) {
            // left
            int pp2{1};
            int cnt{};
            bool visible0{true};
            for (auto xx = x - 1; xx >= 0; --xx) {
                if (x > 0)
                    cnt++;
                if (grid[y][xx] >= grid[y][x]) {
                    visible0 = false;
                    break;
                }
            }
            pp2 *= cnt;
            cnt = 0;

            // right
            bool visible1 = true;
            for (auto xx = x + 1; xx < width; ++xx) {
                if (x + 1 < width)
                    ++cnt;
                if (grid[y][xx] >= grid[y][x]) {
                    visible1 = false;
                    break;
                }
            }

            pp2 *= cnt;
            cnt = 0;

            // up
            bool visible2 = true;
            for (auto yy = y - 1; yy >= 0; --yy) {
                if (y > 0)
                    ++cnt;
                if (grid[yy][x] >= grid[y][x]) {
                    visible2 = false;
                    break;
                }
            }

            pp2 *= cnt;
            cnt = 0;

            // down
            bool visible3 = true;
            for (auto yy = y + 1; yy < height; ++yy) {
                if (y + 1 < height)
                    ++cnt;
                if (grid[yy][x] >= grid[y][x]) {
                    visible3 = false;
                    break;
                }
            }

            pp2 *= cnt;
            p2 = std::max(p2, pp2);

            if (visible0 || visible1 || visible2 || visible3) {
                ++p1;
            }
        }
    }
    return {std::to_string(p1), std::to_string(p2)};
}

REGISTER_FUNC_FOR_DAY(8, day08)
