#include <sstream>
#include <iostream>

int main()
{
    int s0{};
    int s1{};
    char line[4];
    while (std::cin.read(line, 4))
    {
        s0 += 3 * ((-line[0] + line[2] - 1) % 3) + line[2] - 87;
        s1 += (line[0] + line[2] - 1) % 3 + 3 * line[2] - 263;
    }
    std::cout << s0 << '\n'
              << s1 << '\n';
}
