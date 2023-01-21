#include "common.hh"

#include <fmt/core.h>
#include <fmt/color.h>

template <typename Func, typename Ret>
Ret repeat(size_t n, Func& func) {
    for (auto i{0UL}; i < n - 1; ++i) {
        (void)func();
    }
    return func();
}

int main(int argc, char** argv) {
    auto num_runs{argc > 1 ? std::atoi(argv[1]) : 1};
    auto solutions = Runner::get().get_solutions();
    std::sort(std::begin(solutions), std::end(solutions),
              [](auto const& a, auto const& b) { return a.first < b.first; });
    fmt::print("Day                   Part 1                   Part 2         Runtime[µs]\n");
    double total_runtime{};

    std::string deferred_output{};

    for (auto const& [day, func] : solutions) {
        fmt::print("{:>3}", day);
        StopWatch stop_watch{};
        auto const result{repeat<decltype(func), Result>(num_runs, func)};
        auto const runtime = static_cast<double>(stop_watch.elapsed()) / static_cast<double>(num_runs) / 1000.0;

        fmt::print("{:>25}", result.part_1);
        if (result.part_2.length() < 20) {
            fmt::print("{:>25}", result.part_2);
        } else {
            fmt::print("{:>25}", "see below");
            deferred_output = deferred_output + "Day " + std::to_string(day) + " part 2:\n" + result.part_2 + "\n";
        }

        if (runtime < 1000.0) {
            fmt::print(fg(fmt::color::green), "{:>20.2f}\n", runtime);
        } else {
            fmt::print(fg(fmt::color::red), "{:>20.2f}\n", runtime);
        }
        total_runtime += runtime;
    }
    fmt::print("                                                         ----------------\n");
    fmt::print("                                                         Total: {:>9.2f}\n", total_runtime);

    if (!deferred_output.empty()) {
        fmt::print("{}", deferred_output.c_str());
    }
}
