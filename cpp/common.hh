#pragma once

#include <chrono>
#include <cstdint>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <type_traits>

struct Result {
    std::string part_1;
    std::string part_2;
};

class Runner;

class Runner {
  public:
    static void register_day(uint32_t day, std::function<Result()> func);

    static Runner& get();

    std::vector<std::pair<uint32_t, std::function<Result()>>> const& get_solutions() const;

  private:
    std::vector<std::pair<uint32_t, std::function<Result()>>> solutions_{};
};

struct FunctionRegisterer {
    FunctionRegisterer(uint32_t day, std::function<Result()> func) {
        Runner::get().register_day(day, std::move(func));
    }
};

#define REGISTER_FUNC_FOR_DAY(day, func)                                                                               \
    namespace {                                                                                                        \
    FunctionRegisterer _registerer{day, func};                                                                         \
    }

struct StopWatch {
    StopWatch() : begin_{std::chrono::high_resolution_clock::now()} {
    }
    uint64_t elapsed() const {
        auto const now = std::chrono::high_resolution_clock::now();
        return (now - begin_).count();
    }

  private:
    std::chrono::high_resolution_clock::time_point begin_;
};

inline std::string read_file(std::string const& filename) {
    std::ifstream f{filename};
    if (!f.good()) {
        throw std::runtime_error{"unable to open file " + filename};
    }
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

template <typename T, size_t min_length, size_t max_length>
size_t parse(char const* s, T& v) {
    size_t i{};
    v = 0;
    T sgn{1};
    if constexpr (std::is_signed_v<T>) {
        if (s[i] == '-') {
            sgn = -1;
            ++i;
        }
    }
    for (; i < std::max(min_length, max_length) && '0' <= s[i] && s[i] <= '9'; ++i) {
        v = T{10} * v + static_cast<T>(s[i] - '0');
    }
    v = v * sgn;
    return i;
}