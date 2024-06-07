#ifndef LIBJALTOP_HPP_
#define LIBJALTOP_HPP_

extern "C" {

float jaltop_cpu_percentage(int interval_ms);
float jaltop_ram_percentage();
unsigned long jaltop_ram_free();
unsigned long jaltop_ram_total();

} // extern "C"

#endif // LIBJALTOP_HPP_

