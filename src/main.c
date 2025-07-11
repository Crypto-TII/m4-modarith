#include <stdio.h>
#include <time.h>

#include "hal.h"

void bench_modarith(void);
void bench_m4(void);

int main(void) {
    hal_setup(CLOCK_BENCHMARK);

    bench_modarith();
    bench_m4();

    hal_exit_(0);
}
