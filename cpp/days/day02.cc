#include "../common.hh"

#include <array>
#include <sstream>
#include <iostream>

Result day02() {
    auto const input{read_file("../inputs/02.txt")};
    constexpr std::array part1_scores = {4, 8, 3, 1, 5, 9, 7, 2, 6};
    constexpr std::array part2_scores = {3, 4, 8, 1, 5, 9, 2, 6, 7};

    int s0{};
    int s1{};
    for (auto p = std::cbegin(input); p < std::cend(input); p += 4) {
        s0 += part1_scores[(p[0] - 'A') * 3 + (p[2] - 'X')];
        s1 += part2_scores[(p[0] - 'A') * 3 + (p[2] - 'X')];
    }
    return {std::to_string(s0), std::to_string(s1)};
}

REGISTER_FUNC_FOR_DAY(2, day02)
