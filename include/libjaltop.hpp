#ifndef LIBJALTOP_HPP_
#define LIBJALTOP_HPP_

extern "C" {

float jaltop_cpu_usage(int interval_ms);
float jaltop_ram_usage();
unsigned long jaltop_ram_free();
unsigned long jaltop_ram_total();

} // extern "C"

#endif // LIBJALTOP_HPP_

