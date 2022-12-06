#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

int main() {
    constexpr auto num_iters{1};
    for (auto cnt{0}; cnt < num_iters; ++cnt) {
        int p1{}, p2{};
        int i{};
        auto group{static_cast<uint64_t>(-1)};
        std::ifstream fin{"../inputs/03.txt"};
        for (std::string line; std::getline(fin, line);) {
            uint64_t a{}, b{};
            for (auto i{0}; i < line.length() / 2; ++i) {
                a |= 1UL << (line[i] - 65UL);
                b |= 1UL << (line[i + line.length() / 2] - 65UL);
            }

            auto score{[](auto n) {
                int const p{63 - __builtin_clzll(n)};
                return p + ((p <= 25) ? 27 : -31);
            }};

            p1 += score(a & b);

            group &= (a | b);
            if (++i % 3 == 0) {
                p2 += score(group);
                group = static_cast<uint64_t>(-1);
            }
        }

        std::cout << p1 << std::endl;
        std::cout << p2 << std::endl;
    }
}
