#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::vector<int> cals{};
    int cur{};
    for (std::string line; std::getline(std::cin, line);) {
        if (line.empty()) {
            cals.push_back(cur);
            cur = 0;
        } else {
            cur += std::atoi(line.c_str());
        }
    }
    std::nth_element(std::begin(cals), std::begin(cals) + 3, std::end(cals), std::greater{});
    std::cout << std::max(std::max(cals[0], cals[1]), cals[2]) << std::endl;
    std::cout << cals[0] + cals[1] + cals[2] << std::endl;
}
