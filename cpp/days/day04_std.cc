// #include <vectorclass.h>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {
    auto begin{std::chrono::high_resolution_clock::now()};
    for (auto t{0}; t < 100000; ++t) {
        int p1{}, p2{};
        std::ifstream fin{"../inputs/04.txt"};
        for (std::string line; std::getline(fin, line);) {
            auto split = line.find(",");
            auto get_from_to = [](auto s) {
                auto split = s.find("-");
                return std::make_pair(std::atoi(s.substr(0, split).c_str()), std::atoi(s.substr(split + 1).c_str()));
            };
            auto [a0, a1] = get_from_to(line.substr(0, split));
            auto [b0, b1] = get_from_to(line.substr(split + 1));

            if (a0 <= b0 && b1 <= a1 || b0 <= a0 && a1 <= b1)
                p1 += 1;
            if (!(a1 < b0 || b1 < a0))
                p2 += 1;
        }
        std::cout << p1 << " " << p2 << "\n";
    }
    auto end{std::chrono::high_resolution_clock::now()};
    std::cerr << "took " << (end - begin).count() << std::endl;
}
