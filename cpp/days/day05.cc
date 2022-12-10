#include "../common.hh"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <array>

Result day05() {
    int64_t sum{};
    std::ifstream fin{"../inputs/05.txt"};
    std::array<std::vector<char>, 10> stacks;
    for (auto i{0}; i < 10; ++i) {
        stacks[i].reserve(128);
    }
    std::string line;
    for (auto l{0}; l < 8; ++l) {
        std::getline(fin, line);
        for (auto i{0}; i < 10; ++i) {
            auto const c{line[i * 4 + 1]};
            if (c != ' ') {
                stacks[i].push_back(c);
            }
        }
    }
    for (auto& stack : stacks) {
        std::reverse(stack.begin(), stack.end());
    }
    std::getline(fin, line); // numbers
    std::getline(fin, line); // blank line
    std::vector<std::tuple<int, int, int>> instructions;
    instructions.reserve(512);
    while (std::getline(fin, line)) {
        int p = 5;
        int size = line.length() > 18 ? 2 : 1;
        int num = size > 1 ? 10 * (line[p] - '0') + line[p + 1] - '0' : line[p] - '0';
        p += size + 6;
        int from = line[p] - '0';
        p += 1 + 4;
        int to = line[p] - '0';
        instructions.emplace_back(num, from - 1, to - 1);
    }

    auto stacks2 = stacks;
    // p1
    for (auto const& [num, from, to] : instructions) {
        for (auto n{0}; n < num; ++n) {
            stacks2[to].push_back(stacks2[from][stacks[from].size() - 1 - n]);
            stacks[to].push_back(stacks[from][stacks[from].size() - num + n]);
        }
        stacks[from].resize(stacks[from].size() - num);
        stacks2[from].resize(stacks2[from].size() - num);
    }
    std::string p1;
    for (auto const& stack : stacks2) {
        p1 += stack.back();
    }
    std::string p2;
    for (auto const& stack : stacks) {
        p2 += stack.back();
    }
    return {p1, p2};
}

REGISTER_FUNC_FOR_DAY(5, day05)
