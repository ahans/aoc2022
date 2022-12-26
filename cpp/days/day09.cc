#include "../common.hh"

#include <array>
#include <algorithm>
#include <string>
#include <unordered_set>

struct Point {
    int x;
    int y;
    [[nodiscard]] int hash() const {
        return 10007 * x + y;
    }
};

Result day09() {
    auto const in{read_file("../inputs/09.txt")};

    std::unordered_set<int> p1;
    p1.reserve(8192);
    std::unordered_set<int> p2;
    p2.reserve(8192);
    std::array<Point, 10> knots{};
    p1.insert(knots.front().hash());
    p2.insert(knots.front().hash());
    for (auto i{0UL}; i < std::size(in);) {
        auto const c{in[i]};
        i += 2;
        uint32_t n;
        i += parse<uint32_t, 1, 2>(&in[i], n) + 1;

        auto const d{[c]() {
            switch (c) {
            case 'L':
                return Point{-1, 0};
            case 'R':
                return Point{1, 0};
            case 'U':
                return Point{0, -1};
            case 'D':
                return Point{0, 1};
            }
            __builtin_unreachable();
        }()};

        for (auto j{0U}; j < n; ++j) {
            knots.front().x += d.x;
            knots.front().y += d.y;
            for (auto j{1UL}; j < knots.size(); ++j) {
                auto const xd{knots[j - 1].x - knots[j].x};
                auto const yd{knots[j - 1].y - knots[j].y};
                if (std::abs(xd) < 2 && std::abs(yd) < 2) {
                    break;
                }
                if (std::abs(xd) > 0) {
                    knots[j].x = xd > 0 ? knots[j].x + 1 : knots[j].x - 1;
                }
                if (std::abs(yd) > 0) {
                    knots[j].y = yd > 0 ? knots[j].y + 1 : knots[j].y - 1;
                }
            }
            p1.insert(knots[1].hash());
            p2.insert(knots.back().hash());
        }
    }
    return {std::to_string(std::size(p1)), std::to_string(std::size(p2))};
}

REGISTER_FUNC_FOR_DAY(9, day09)
