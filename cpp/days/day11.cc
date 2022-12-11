#include "../common.hh"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>
#include <functional>

Result day11() {
    std::ifstream in{"../inputs/11.txt"};
    std::vector<std::vector<uint64_t>> items;
    std::vector<std::function<uint64_t(uint64_t)>> ops;
    std::vector<uint64_t> mods;
    std::vector<std::array<uint64_t, 2>> tos;
    uint64_t n{1};
    for (std::string line; std::getline(in, line);) {
        if (line[0] == 'M')
            continue;
        if (line[2] == 'O') {
            char const op = line[23];
            if (op == '+') {
                if (line[25] == 'o') {
                    auto f = [](uint64_t x) { return x + x; };
                    ops.push_back(std::move(f));
                } else {
                    uint64_t n = std::atoi(line.substr(25).c_str());
                    auto f = [n](uint64_t x) { return x + n; };
                    ops.push_back(std::move(f));
                }
            } else {
                if (line[25] == 'o') {
                    auto f = [](uint64_t x) { return x * x; };
                    ops.push_back(std::move(f));
                } else {
                    uint64_t n = std::atoi(line.substr(25).c_str());
                    auto f = [n](uint64_t x) { return x * n; };
                    ops.push_back(std::move(f));
                }
            }
            continue;
        }
        if (line[2] == 'S') {
            std::vector<uint64_t> its;
            for (auto p = 18U; p < line.length(); p += 4) {
                its.push_back(std::atoi(line.substr(p, p + 4).c_str()));
            }
            items.push_back(std::move(its));
            continue;
        }
        if (line[2] == 'T') {
            int mod = std::atoi(line.substr(20).c_str());
            n *= mod;
            mods.push_back(mod);
            std::getline(in, line);
            int to_true = line.back() - '0';
            std::getline(in, line);
            int to_false = line.back() - '0';
            tos.push_back({to_true, to_false});
            continue;
        }
    }

    auto items_bak = items;
    Result r{};
    {
        std::array<uint64_t, 8> counts{};
        for (auto round{0}; round < 20; ++round) {
            for (auto i{0}; i < 8; ++i) {
                for (auto const& item : items[i]) {
                    ++counts[i];
                    auto n = ops[i](item) / 3;
                    if (n % mods[i] == 0) {
                        items[tos[i][0]].push_back(n);
                    } else {
                        items[tos[i][1]].push_back(n);
                    }
                }
                items[i].clear();
            }
        }
        std::nth_element(counts.begin(), counts.begin() + 2, counts.end(), std::greater{});
        r.part_1 = std::to_string(counts[0] * counts[1]);
    }
    items = std::move(items_bak);
    {
        std::array<uint64_t, 8> counts{};
        for (auto round{0}; round < 10000; ++round) {
            for (auto i{0}; i < 8; ++i) {
                for (auto const& item : items[i]) {
                    ++counts[i];
                    auto ni = ops[i](item) % 223092870;
                    if (ni % mods[i] == 0) {
                        items[tos[i][0]].push_back(ni);
                    } else {
                        items[tos[i][1]].push_back(ni);
                    }
                }
                items[i].clear();
            }
        }
        std::nth_element(counts.begin(), counts.begin() + 2, counts.end(), std::greater{});
        r.part_2 = std::to_string(counts[0] * counts[1]);
    }

    return r;
}

REGISTER_FUNC_FOR_DAY(11, day11)
