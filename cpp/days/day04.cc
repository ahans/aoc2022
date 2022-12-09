#include "../common.hh"

#include <vectorclass.h>

#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

Result day04() {
    auto const input{read_file("../inputs/04.txt")};
    int p1{}, p2{};
    constexpr bool vectorize{true};
    constexpr auto batch_size{64};
    std::array<std::array<char, batch_size>, 4> a;
    auto const process_batch{[&a, &p1, &p2] {
        std::array<Vec64c, 4> aa;
        for (auto k{0}; k < 4; ++k)
            aa[k].load(a[k].data());
        p1 += horizontal_count((aa[0] <= aa[2] && aa[3] <= aa[1]) || (aa[2] <= aa[0] && aa[1] <= aa[3]));
        p2 += horizontal_count(!(aa[1] < aa[2] || aa[3] < aa[0]));
    }};
    int i{};
    for (auto p = input.cbegin(); p < input.cend();) {
        p += parse<char, 1, 2>(&*p, a[0][i]);
        p += 1; // -
        p += parse<char, 1, 2>(&*p, a[1][i]);
        p += 1; // ,
        p += parse<char, 1, 2>(&*p, a[2][i]);
        p += 1; // -
        p += parse<char, 1, 2>(&*p, a[3][i]);
        p += 1; // \n

        if constexpr (vectorize) {
            ++i;

            if (i == batch_size) {
                i = 0;
                process_batch();
            }
        } else {
            if ((a[0][i] <= a[2][i] && a[3][i] <= a[1][i]) || (a[2][i] <= a[0][i] && a[1][i] <= a[3][i]))
                p1 += 1;
            if (!(a[1][i] < a[2][i] || a[3][i] < a[0][i]))
                p2 += 1;
        }
    }
    if constexpr (vectorize) {
        for (; i < batch_size; ++i) {
            a[0][i] = a[1][i] = 0;
            a[2][i] = a[3][i] = 1;
        }
        process_batch();
    }

    return {std::to_string(p1), std::to_string(p2)};
}

REGISTER_FUNC_FOR_DAY(4, day04)