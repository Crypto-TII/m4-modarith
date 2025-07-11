// =============================================
// ==    Classification: TII CONFIDENTIAL     ==
// =============================================

// Some of the code in this file has been reused from the pqm4 project: https://github.com/mupq/pqm4

#include "hal.h"

#include <errno.h>
#include <libopencm3/cm3/dwt.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/rng.h>
#include <libopencm3/stm32/usart.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// https://github.com/libopencm3/libopencm3-examples/blob/master/examples/stm32/f1/stm32-h103/traceswo/traceswo.c

#include <libopencm3/cm3/itm.h>
#include <libopencm3/cm3/scs.h>
#include <libopencm3/cm3/tpiu.h>
#include <libopencm3/stm32/dbgmcu.h>

/* USART2, used only for QEMU */
#define RCC_USARTx RCC_USART2
#define USARTx USART2
#define RCC_GPIOx RCC_GPIOA
#define GPIOx GPIOA
#define GPIO_AFx GPIO_AF7
#define GPIOtx GPIO2  // PA2
#define GPIOrx GPIO3  // PA3

#ifdef STM32F4DISCOVERY
#define IDCODE 0x413
/* 24 MHz */
const struct rcc_clock_scale benchmarkclock = {
    .pllm = 8,    // VCOin = HSE / PLLM = 1 MHz
    .plln = 192,  // VCOout = VCOin * PLLN = 192 MHz
    .pllp = 8,    // PLLCLK = VCOout / PLLP = 24 MHz (low to have 0WS)
    .pllq = 4,    // PLL48CLK = VCOout / PLLQ = 48 MHz (required for USB, RNG)
    .pllr = 0,
    .hpre = RCC_CFGR_HPRE_DIV_NONE,
    .ppre1 = RCC_CFGR_PPRE_DIV_2,
    .ppre2 = RCC_CFGR_PPRE_DIV_NONE,
    .pll_source = RCC_CFGR_PLLSRC_HSE_CLK,
    .voltage_scale = PWR_SCALE1,
    .flash_config = FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_LATENCY_0WS,
    .ahb_frequency = 24000000,
    .apb1_frequency = 12000000,
    .apb2_frequency = 24000000,
};
#elif defined(NUCLEO_L4R5ZI)
#define IDCODE 0x470

/* Patched function for newer PLL not yet supported by opencm3 */
void _rcc_set_main_pll(uint32_t source, uint32_t pllm, uint32_t plln, uint32_t pllp, uint32_t pllq, uint32_t pllr) {
    RCC_PLLCFGR = (RCC_PLLCFGR_PLLM(pllm) << RCC_PLLCFGR_PLLM_SHIFT) | (plln << RCC_PLLCFGR_PLLN_SHIFT) |
                  ((pllp & 0x1Fu) << 27u) | /* NEWER PLLP */
                  (source << RCC_PLLCFGR_PLLSRC_SHIFT) | (pllq << RCC_PLLCFGR_PLLQ_SHIFT) |
                  (pllr << RCC_PLLCFGR_PLLR_SHIFT) | RCC_PLLCFGR_PLLREN;
}
#else
#error Invalid development board, must define either STM32F4DISCOVERY or NUCLEO_L4R5ZI
#endif

int isQEMU = 0;

__attribute__((constructor)) static void test_QEMU() {

    if ((DBGMCU_IDCODE & 0xFFF) == IDCODE) {
        isQEMU = 0;
    }
    else {
#ifdef STM32F4DISCOVERY
        isQEMU = 1;
#else
        // Other boards are not supported by QEMU
        while (1) {
        }
#endif
    }
}

static void trace_send_blocking(char c) {
    if (isQEMU) {
        usart_send_blocking(USARTx, c);
    }
    else {
        while (!(ITM_STIM8(0) & ITM_STIM_FIFOREADY))
            ;

        ITM_STIM8(0) = c;
    }
}

int _write(int file, char *ptr, int len);

uint64_t tick_per_sec;

__attribute__((unused)) static uint32_t _clock_freq;

#ifdef STM32F4DISCOVERY
static void clock_setup(const enum clock_mode clock) {
    switch (clock) {
        case CLOCK_BENCHMARK:
            rcc_clock_setup_pll(&benchmarkclock);
            tick_per_sec = 24000000LLU;
            break;
        case CLOCK_QEMU:  // qemu seems not to support clock initialization
            break;
        case CLOCK_FAST:
        default:
            rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
            tick_per_sec = 168000000LLU;
            break;
    }

    rcc_periph_clock_enable(RCC_GPIOx);
    rcc_periph_clock_enable(RCC_USARTx);
    rcc_periph_clock_enable(RCC_DMA1);
    rcc_periph_clock_enable(RCC_RNG);

    flash_prefetch_enable();
}
#elif defined(NUCLEO_L4R5ZI)
static void clock_setup(const enum clock_mode clock) {
    rcc_periph_clock_enable(RCC_PWR);
    rcc_periph_clock_enable(RCC_SYSCFG);
    pwr_set_vos_scale(PWR_SCALE1);
    /* The L4R5ZI chip also needs the R1MODE bit in PWR_CR5 register set, but
       OpenCM3 doesn't support this yet. But luckily the default value for the bit
       is 1. */
    switch (clock) {
        case CLOCK_BENCHMARK:
            /* Benchmark straight from the HSI16 without prescaling */
            rcc_osc_on(RCC_HSI16);
            rcc_wait_for_osc_ready(RCC_HSI16);
            rcc_ahb_frequency = 20000000;
            rcc_apb1_frequency = 20000000;
            rcc_apb2_frequency = 20000000;
            _clock_freq = 20000000;
            rcc_set_hpre(RCC_CFGR_HPRE_NODIV);
            rcc_set_ppre1(RCC_CFGR_PPRE_NODIV);
            rcc_set_ppre2(RCC_CFGR_PPRE_NODIV);
            rcc_osc_off(RCC_PLL);
            while (rcc_is_osc_ready(RCC_PLL))
                ;
            /* Configure the PLL oscillator (use CUBEMX tool -> scale HSI16 to 20MHz). */
            _rcc_set_main_pll(RCC_PLLCFGR_PLLSRC_HSI16, 1, 10, 2, RCC_PLLCFGR_PLLQ_DIV2, RCC_PLLCFGR_PLLR_DIV8);
            /* Enable PLL oscillator and wait for it to stabilize. */
            rcc_osc_on(RCC_PLL);
            flash_dcache_enable();
            flash_icache_enable();
            flash_set_ws(FLASH_ACR_LATENCY_0WS);
            flash_prefetch_enable();
            rcc_set_sysclk_source(RCC_CFGR_SW_PLL);
            rcc_wait_for_sysclk_status(RCC_PLL);
            break;
        case CLOCK_FAST:
        default:
            rcc_osc_on(RCC_HSI16);
            rcc_wait_for_osc_ready(RCC_HSI16);
            rcc_ahb_frequency = 120000000;
            rcc_apb1_frequency = 120000000;
            rcc_apb2_frequency = 120000000;
            _clock_freq = 120000000;
            rcc_set_hpre(RCC_CFGR_HPRE_NODIV);
            rcc_set_ppre1(RCC_CFGR_PPRE_NODIV);
            rcc_set_ppre2(RCC_CFGR_PPRE_NODIV);
            rcc_osc_off(RCC_PLL);
            while (rcc_is_osc_ready(RCC_PLL))
                ;
            /* Configure the PLL oscillator (use CUBEMX tool -> scale HSI16 to 120MHz). */
            _rcc_set_main_pll(RCC_PLLCFGR_PLLSRC_HSI16, 1, 15, 2, RCC_PLLCFGR_PLLQ_DIV2, RCC_PLLCFGR_PLLR_DIV2);
            /* Enable PLL oscillator and wait for it to stabilize. */
            rcc_osc_on(RCC_PLL);
            rcc_wait_for_osc_ready(RCC_PLL);
            flash_dcache_enable();
            flash_icache_enable();
            flash_set_ws(0x05);
            flash_prefetch_enable();
            rcc_set_sysclk_source(RCC_CFGR_SW_PLL);
            rcc_wait_for_sysclk_status(RCC_PLL);
            break;
    }
    rcc_osc_on(RCC_HSI48); /* HSI48 must always be on for RNG */
    rcc_wait_for_osc_ready(RCC_HSI48);
    rcc_periph_clock_enable(RCC_RNG);
    rcc_set_clock48_source(RCC_CCIPR_CLK48SEL_HSI48);
    rng_enable();
}
#endif

static void gpio_setup(void) {
    gpio_mode_setup(GPIOx, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIOtx | GPIOrx);
    gpio_set_af(GPIOx, GPIO_AFx, GPIOtx | GPIOrx);
}

static void usart_setup(int baud) {
    usart_set_baudrate(USARTx, baud);
    usart_set_databits(USARTx, 8);
    usart_set_stopbits(USARTx, USART_STOPBITS_1);
    usart_set_mode(USARTx, USART_MODE_TX_RX);
    usart_set_parity(USARTx, USART_PARITY_NONE);
    usart_set_flow_control(USARTx, USART_FLOWCONTROL_NONE);

    usart_enable(USARTx);
}

static void systick_setup(void) {
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_set_reload(16777215);
    systick_interrupt_enable();
    systick_counter_enable();
}

/**
 * Use SWO or USART as a console.
 * This is a syscall for newlib
 * @param file
 * @param ptr
 * @param len
 * @return
 */
#ifdef __clang__
static int trace_putc(char c, FILE *file) {
    (void)file;             /* Not used in this function */
    trace_send_blocking(c); /* Defined by underlying system */
    return c;
}

static int null_getc(FILE *file) {
    (void)file; /* Not used in this function */
    return 0;
}

static FILE __stdio = FDEV_SETUP_STREAM(trace_putc, null_getc, NULL, _FDEV_SETUP_RW);

FILE *const stdin = &__stdio;
__strong_reference(stdin, stdout);
__strong_reference(stdin, stderr);
#else
int _write(int file, char *ptr, int len) {
    int i;

    if (file == STDOUT_FILENO || file == STDERR_FILENO) {
        for (i = 0; i < len; i++) {
            trace_send_blocking(ptr[i]);
        }
        return i;
    }
    errno = EIO;
    return -1;
}
#endif

int usleep(useconds_t usec) {
    uint64_t t0 = hal_get_time();
    while ((hal_get_time() - t0) < ((uint64_t)usec * tick_per_sec) / 1000000ULL)
        ;
    t0 = hal_get_time() - t0;
    return 0;
}

void hal_setup_m4(const enum clock_mode clock) {
    if (isQEMU) {
        (void)clock;
        clock_setup(CLOCK_QEMU);
        gpio_setup();
        usart_setup(115200);
    }
    else {
        clock_setup(clock);
    }

    systick_setup();
    dwt_enable_cycle_counter();
    // add 0.1 sec delay
    usleep(100000);
}

static volatile unsigned long long overflowcnt = 0;
void sys_tick_handler(void) {
    ++overflowcnt;
}

uint64_t hal_get_time() {
    while (true) {
        unsigned long long before = overflowcnt;
        unsigned long long result = (before + 1) * 16777216llu - systick_get_value();
        if (overflowcnt == before) {
            return result;
        }
    }
}

void hal_exit_(int retcode) {
    if (isQEMU) {
        int ret[] = {0x20026, retcode};
        __asm__ volatile("" ::: "memory");
        __asm__ volatile(
            "mov  r0, #0x20 \n"
            "mov  r1, %[ret]\n"
            "bkpt #0xAB     \n"
            :
            : [ret] "r"(ret)
            : "r0", "r1");
    }
    else {
#if defined(STM32F4DISCOVERY) || defined(NUCLEO_L4R5ZI)
        printf("---------- Program exited with return code %d ----------\n", retcode);
        while (1) {
            __asm volatile("NOP");
        }
#else
        exit(retcode);
#endif
    }
}
