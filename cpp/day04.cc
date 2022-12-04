#include <vectorclass.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    int num_trials{1};
    if (argc > 1) num_trials = std::atoi(argv[1]);
    auto begin{std::chrono::high_resolution_clock::now()};

    for (auto t{0}; t < num_trials; ++t)
    {
        std::ifstream fin{"../inputs/04.txt"};
        int p1{}, p2{};
        std::array<char, 32> a0, a1, b0, b1;
        auto process_batch = [&] {
            Vec32c aa0, aa1, bb0, bb1;
            aa0.load(a0.data());
            aa1.load(a1.data());
            bb0.load(b0.data());
            bb1.load(b1.data());
            p1 += horizontal_count(aa0 <= bb0 && bb1 <= aa1 || bb0 <= aa0 && aa1 <= bb1);
            p2 += horizontal_count(!(aa1 < bb0 || bb1 < aa0));
        };
        int i{};
        for (std::string line; std::getline(fin, line);)
        {
            int p{};
            a0[i] = line[p++] - '0';
            if (line[p] != '-')
                a0[i] = a0[i] * 10 + (line[p++] - '0');
            ++p; // skip -
            a1[i] = line[p++] - '0';
            if (line[p] != ',')
                a1[i] = a1[i] * 10 + (line[p++] - '0');
            ++p; // skip ,

            b0[i] = line[p++] - '0';
            if (line[p] != '-')
                b0[i] = b0[i] * 10 + (line[p++] - '0');
            ++p; // skip -
            b1[i] = line[p++] - '0';
            if (p < line.length())
                b1[i] = b1[i] * 10 + (line[p] - '0');

            ++i;

            if (i == 32)
            {
                i = 0;
                process_batch();
            }
        }
        for (; i < 32; ++i)
        {
            a0[i] = a1[i] = 0;
            b0[i] = b1[i] = 1;
        }
        process_batch();

        std::cout << p1 << " " << p2 << "\n";
    }
    auto end{std::chrono::high_resolution_clock::now()};
    std::cerr << "took " << (end - begin).count() << std::endl;
}
