#include "../common.hh"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

Result day03() {
    int p1{}, p2{}, i{};
    auto group{static_cast<uint64_t>(-1)};
    auto input = read_file("../inputs/03.txt");
    std::string_view view{input};
    for (auto p{0UL}; p < view.length();) {
        uint64_t a{}, b{};

        auto const len{view.substr(p).find_first_of('\n')};

        for (auto i{0UL}; i < len / 2; ++i) {
            a |= 1UL << (view[p + i] - 65UL);
            b |= 1UL << (view[p + i + len / 2] - 65UL);
        }

        p += len + 1;

        constexpr auto score{[](auto n) {
            int const p{__builtin_ctzll(n)};
            return p + ((p <= 25) ? 27 : -31);
        }};

        p1 += score(a & b);

        group &= (a | b);
        if (++i % 3 == 0) {
            p2 += score(group);
            group = static_cast<uint64_t>(-1);
        }
    }

    return {std::to_string(p1), std::to_string(p2)};
}

REGISTER_FUNC_FOR_DAY(3, day03)
