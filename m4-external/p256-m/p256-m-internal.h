#ifndef P256_M_INTERNAL_H
#define P256_M_INTERNAL_H

#include <stdint.h>

typedef struct {
    uint32_t m[8];
    uint32_t R2[8];
    uint32_t ni;
} m256_mod;

extern const m256_mod p256_p;

void m256_mul(uint32_t z[8], const uint32_t x[8], const uint32_t y[8], const m256_mod *mod);

#endif  // P256_M_INTERNAL_H
