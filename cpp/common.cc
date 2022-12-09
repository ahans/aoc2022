#include "common.hh"

void Runner::register_day(uint32_t day, std::function<Result()> func) {
    get().solutions_.emplace_back(day, func);
}

Runner& Runner::get() {
    static Runner runner{};
    return runner;
}

std::vector<std::pair<uint32_t, std::function<Result()>>> const& Runner::get_solutions() const {
    return solutions_;
}
