#include "libjaltop.hpp"

#include <sys/sysinfo.h>

#include <limits>

constexpr auto NaN = std::numeric_limits<float>::quiet_NaN();

extern "C" {

float jaltop_ram_percentage() {
    struct sysinfo sysinfo;
    const auto retval = ::sysinfo(&sysinfo);

    if (retval != 0) {
        return NaN;
    }

    return 1.0 * sysinfo.freeram / sysinfo.totalram;
}

unsigned long jaltop_ram_free() {
    struct sysinfo sysinfo;
    const auto retval = ::sysinfo(&sysinfo);

    if (retval != 0) {
        return 0;
    }

    return sysinfo.freeram;
}

unsigned long jaltop_ram_total() {
    struct sysinfo sysinfo;
    const auto retval = ::sysinfo(&sysinfo);

    if (retval != 0) {
        return 0;
    }

    return sysinfo.totalram;
}

} // extern "C"
