#include "../common.hh"

#include <array>
#include <fstream>
#include <sstream>
#include <iostream>

Result day06() {

    auto buf = read_file("../inputs/06.txt");
    auto const len{buf.length()};

    auto const update{[&buf](auto const i, auto& hist, auto& unique, auto const n) {
        auto const c_in{buf[i] - 'a'};
        ++hist[c_in];
        if (hist[c_in] == 1)
            ++unique;
        if (i >= n) {
            auto const c_out{buf[i - n] - 'a'};
            --hist[c_out];
            if (hist[c_out] == 0)
                --unique;
            if (unique == n)
                return true;
        }
        return false;
    }};

    std::array<unsigned int, 26> hist4{}, hist14{};
    unsigned int unique4{}, unique14{};

    int p1, p2;
    for (auto i{0UL}; i < len; ++i) {
        if (unique4 < 4U && update(i, hist4, unique4, 4U))
            p1 = i + 1;
        if (update(i, hist14, unique14, 14U)) {
            p2 = i + 1;
            break;
        }
    }
    return {std::to_string(p1), std::to_string(p2)};
}

REGISTER_FUNC_FOR_DAY(6, day06)
