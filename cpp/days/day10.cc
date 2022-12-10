#include "../common.hh"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

Result day10() {
    auto const input{read_file("../inputs/10.txt")};
    int p1{};
    std::string p2{};
    p2.reserve(40 * 6);
    int cycle = 0;
    int x = 1;
    int xn = 1;
    int cycles_left = 0;
    for (auto p = std::cbegin(input); p < std::cend(input);) {
        constexpr std::string_view noop{"noop"};
        constexpr std::string_view addx{"addx"};

        cycle += 1;

        if (cycles_left > 0) {
            --cycles_left;
        } else {
            x = xn;
            if (*p == noop[0]) {
                p += noop.length();
            } else {
                p += addx.length() + 1;
                int n;
                p += parse<int, 2, 3>(&*p, n);
                xn = xn + n;
                cycles_left = 1;
            }
            p += 1; // \n
        }

        if ((cycle - 20) % 40 == 0) {
            p1 += cycle * x;
        }
        auto const col{(cycle - 1) % 40};
        p2 += (col >= x - 1 && col <= x + 1) ? '#' : ' ';
        if (col == 39)
            p2 += '\n';
    }
    return {std::to_string(p1), p2};
}

REGISTER_FUNC_FOR_DAY(10, day10)
