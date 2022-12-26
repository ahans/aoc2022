#include "../common.hh"

#include <array>
#include <algorithm>
#include <string>

[[nodiscard]] std::string to_snafu(uint64_t d) {
    std::string snafu;
    constexpr std::array lut = {'0', '1', '2', '=', '-'};
    while (d > 0) {
        snafu.push_back(lut[d % 5]);
        d = (d + 2) / 5;
    }
    std::reverse(std::begin(snafu), std::end(snafu));
    return snafu;
}

Result day25() {
    auto const in{read_file("../inputs/25.txt")};
    int64_t s{};
    int64_t cur{};
    for (auto i{0UL}; i < in.length();) {
        switch (in[i++]) {
        case '\n':
            s += cur;
            cur = 0;
            break;
        case '=':
            cur = cur * 5 - 2;
            break;
        case '-':
            cur = cur * 5 - 1;
            break;
        case '0':
            cur = cur * 5;
            break;
        case '1':
            cur = cur * 5 + 1;
            break;
        case '2':
            cur = cur * 5 + 2;
            break;
        }
    }
    return {to_snafu(s), ""};
}

REGISTER_FUNC_FOR_DAY(25, day25)
