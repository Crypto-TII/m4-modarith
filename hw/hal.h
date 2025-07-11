// =============================================
// ==    Classification: TII CONFIDENTIAL     ==
// =============================================

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libopencmsis/core_cm3.h>
#include <libopencm3/cm3/dwt.h>

#ifndef HAL_H
#define HAL_H

#define bm_decls uint32_t bm_s, bm_e
#define bm_start() do { __disable_irq(); bm_s = DWT_CYCCNT; } while(0)
#define bm_end() do { bm_e = DWT_CYCCNT; __enable_irq(); } while(0)
#define bm_result() (bm_e - bm_s)

enum clock_mode { CLOCK_FAST, CLOCK_BENCHMARK, CLOCK_QEMU };

extern int isQEMU;

int usleep(useconds_t usec);
void hal_setup_m4(enum clock_mode clock);
uint64_t hal_get_time(void);
void hal_exit_(int retcode);

#define hal_setup(clock) hal_setup_m4(clock)

#endif
