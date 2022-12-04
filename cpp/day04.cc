#include <vectorclass.h>

#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    int num_trials{1};
    if (argc > 1) num_trials = std::atoi(argv[1]);

    auto const begin{std::chrono::high_resolution_clock::now()};

    for (auto t{0}; t < num_trials; ++t) {
        std::ifstream fin{"../inputs/04.txt"};
        int p1{}, p2{};
	std::array<std::array<char, 64>, 4> a;
        auto const process_batch = [&a, &p1, &p2] {
	    std::array<Vec32c, 4> aa;
	    for (auto k{0}; k < 4; ++k) aa[k].load(a[k].data());
            p1 += horizontal_count(aa[0] <= aa[2] && aa[3] <= aa[1] || aa[2] <= aa[0] && aa[1] <= aa[3]);
            p2 += horizontal_count(!(aa[1] < aa[2] || aa[3] < aa[0]));
        };
        int i{};
        for (std::string line; std::getline(fin, line);) {
            int p{};
            a[0][i] = line[p++] - '0';
            if (line[p] != '-') a[0][i] = a[0][i] * 10 + (line[p++] - '0');
            ++p;
            a[1][i] = line[p++] - '0';
            if (line[p] != ',') a[1][i] = a[1][i] * 10 + (line[p++] - '0');
            ++p;

            a[2][i] = line[p++] - '0';
            if (line[p] != '-') a[2][i] = a[2][i] * 10 + (line[p++] - '0');
            ++p;
            a[3][i] = line[p++] - '0';
            if (p < line.length()) a[3][i] = a[3][i] * 10 + (line[p] - '0');

            ++i;

            if (i == 32) {
                i = 0;
                process_batch();
            }
        }
        for (; i < 32; ++i) {
            a[0][i] = a[1][i] = 0;
            a[1][i] = a[2][i] = 1;
        }
        process_batch();

        std::cout << p1 << " " << p2 << "\n";
    }
    auto const end{std::chrono::high_resolution_clock::now()};
    std::cerr << "took " << (end - begin).count() << std::endl;
}
