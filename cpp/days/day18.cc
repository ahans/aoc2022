#include "../common.hh"

#include <array>

Result day18() {
    std::vector<bool> voxels(32 * 32 * 32);

    constexpr auto index = [](auto const x, auto const y, auto const z) { return x * 32 * 32 + y * 32 + z; };

    constexpr std::array<int[3], 6> ds = {{{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}}};

    int lower_x{999999}, lower_y{999999}, lower_z{999999};
    int upper_x{}, upper_y{}, upper_z{};
    int num_voxels{};
    auto const in{read_file("../inputs/18.txt")};
    for (auto i{0UL}; i < in.length();) {
        int x, y, z;
        i += parse<int, 1, 2>(&in[i], x) + 1;
        x += 1;
        i += parse<int, 1, 2>(&in[i], y) + 1;
        y += 1;
        i += parse<int, 1, 2>(&in[i], z) + 1;
        z += 1;

        ++num_voxels;
        upper_x = std::max(x, upper_x);
        upper_y = std::max(y, upper_y);
        upper_z = std::max(z, upper_z);
        lower_x = std::min(x, lower_x);
        lower_y = std::min(y, lower_y);
        lower_z = std::min(z, lower_z);
        voxels[index(x, y, z)] = true;
    }
    int num_shared{};
    for (auto x = lower_x; x <= upper_x; ++x) {
        for (auto y = lower_y; y <= upper_y; ++y) {
            for (auto z = lower_z; z <= upper_z; ++z) {
                if (!voxels[index(x, y, z)])
                    continue;
                for (auto [dx, dy, dz] : ds) {
                    if (voxels[index(x + dx, y + dy, z + dz)]) {
                        ++num_shared;
                    }
                }
            }
        }
    }
    std::array<std::array<int, 3>, 32 * 32 * 32> queue;
    auto* front = queue.begin();
    auto* back = queue.begin();
    *back++ = {0, 0, 0};
    int p2{};
    std::vector<bool> seen(32 * 32 * 32);
    seen[0] = true;
    while (front != back) {
        auto const [x, y, z]{*front++};

        for (auto [dx, dy, dz] : ds) {
            int nx = x + dx;
            int ny = y + dy;
            int nz = z + dz;
            if (nx < 0 || nx >= 32 || ny < 0 || ny >= 32 || nz < 0 || nz >= 32) {
                continue;
            }
            auto idx = index(nx, ny, nz);
            if (seen[idx]) {
                continue;
            }
            if (voxels[idx]) {
                ++p2;
            } else {
                seen[idx] = true;
                *back++ = {nx, ny, nz};
            }
        }
    }

    return {std::to_string(num_voxels * 6 - num_shared), std::to_string(p2)};
}

REGISTER_FUNC_FOR_DAY(18, day18)
