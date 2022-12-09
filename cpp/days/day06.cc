#include <array>
#include <fstream>
#include <sstream>
#include <iostream>

int main(int argc, char** argv) {
    auto const num_trials{argc > 1 ? std::atoi(argv[1]) : 1};
    for (auto t{0}; t < num_trials; ++t) {
        std::stringstream ss;
        std::ifstream in{"../inputs/06.txt"};
        ss << in.rdbuf();
        auto buf = ss.str();
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

        for (auto i{0UL}; i < len; ++i) {
            if (unique4 < 4U && update(i, hist4, unique4, 4U))
                std::cout << i + 1 << std::endl;
            if (update(i, hist14, unique14, 14U)) {
                std::cout << i + 1 << std::endl;
                break;
            }
        }
    }
}
