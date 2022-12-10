#include "../common.hh"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

Result day01() {
    auto const input{read_file("../inputs/01.txt")};
    std::vector<int> cals{};
    int cur{};
    for (auto p = std::cbegin(input); p < std::cend(input);) {
        int val;
        p += parse<int, 4, 5>(&*p, val);
        ++p; // newline
        if (*p == '\n') {
            cals.push_back(cur);
            cur = 0;
            ++p;
        } else {
            cur += val;
        }
    }
    std::partial_sort(std::begin(cals), std::begin(cals) + 3, std::end(cals), std::greater{});
    return {std::to_string(cals[2]), std::to_string(cals[0] + cals[1] + cals[2])};
}

REGISTER_FUNC_FOR_DAY(1, day01)
