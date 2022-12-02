#include <numeric>
#include <iostream>
#include <sstream>

int main()
{
    std::stringstream buffer;
    buffer << std::cin.rdbuf();
    std::string const s{buffer.str()};
    using Line = char[4];
    auto const result{std::transform_reduce(
        reinterpret_cast<Line const *>(s.c_str()),
        reinterpret_cast<Line const *>(s.c_str() + s.length()),
        std::make_pair(0, 0),
        [](auto const a, auto const b)
        {
            return std::make_pair(a.first + b.first, a.second + b.second);
        },
        [](auto const line)
        {
            auto const a{line[0] - 'A'};
            auto const b{line[2] - 'X'};
            return std::make_pair(
                3 * ((b - a + 4) % 3) + b + 1,
                (a + b + 2) % 3 + 3 * b + 1);
        })};
    std::cout << result.first << std::endl;
    std::cout << result.second << std::endl;
}