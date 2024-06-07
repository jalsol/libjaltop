#include "libjaltop.hpp"

#include <optional>
#include <fstream>
#include <thread>
#include <chrono>
#include <limits>

constexpr auto NaN = std::numeric_limits<float>::quiet_NaN();

namespace {

struct Jiffies {
    unsigned long long total;
    unsigned long long work;
};

std::optional<Jiffies> parse_from_system() {
    std::ifstream in("/proc/stat");

    if (!in) {
        return std::nullopt;
    }

    std::string label;
    unsigned long long user, nice, system, idle, iowait, irq, softirq;
    in >> label >> user >> nice >> system >> idle >> iowait >> irq >> softirq;

    Jiffies result;
    result.total = user + nice + system + idle + iowait + irq + softirq;
    result.work  = user + nice + system;
    return result;
}

} // namespace

extern "C"
float jaltop_cpu_usage(int interval_ms) {
    static std::optional<Jiffies> latest_jiffies = std::nullopt;
    static auto result = NaN;

    const auto previous_jiffies = [&] {
        if (interval_ms > 0) {
            return parse_from_system();
        }

        if (!latest_jiffies.has_value()) {
            latest_jiffies = parse_from_system();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        return latest_jiffies;
    }();

    if (!previous_jiffies.has_value()) {
        return NaN;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));

    const auto current_jiffies = parse_from_system();

    if (!current_jiffies.has_value()) {
        return NaN;
    }

    const auto total_diff = current_jiffies->total - previous_jiffies->total;
    const auto work_diff  = current_jiffies->work  - previous_jiffies->work;

    latest_jiffies = current_jiffies;

    if (total_diff != 0) {
        result = 1.0f * work_diff / total_diff;
    }

    return result;
}

