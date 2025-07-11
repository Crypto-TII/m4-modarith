/*  Written in 2019 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include "xoshiro128plusplus.h"

#include <stdint.h>

/* This is xoshiro128++ 1.0, one of our 32-bit all-purpose, rock-solid
   generators. It has excellent speed, a state size (128 bits) that is
   large enough for mild parallelism, and it passes all tests we are aware
   of.

   For generating just single-precision (i.e., 32-bit) floating-point
   numbers, xoshiro128+ is even faster.

   The state must be seeded so that it is not everywhere zero. */

#define ROTL(x, k) (((x) << (k)) | ((x) >> (32 - (k))))

void xoshiro128plusplus_seed(xoshiro128plusplus_state state, const uint32_t seed[4]) {
    state[0] = seed[0];
    state[1] = seed[1];
    state[2] = seed[2];
    state[3] = seed[3];
}

uint32_t xoshiro128plusplus_rand32(xoshiro128plusplus_state state) {
    const uint32_t result = ROTL(state[0] + state[3], 7) + state[0];

    const uint32_t t = state[1] << 9;

    state[2] ^= state[0];
    state[3] ^= state[1];
    state[1] ^= state[2];
    state[0] ^= state[3];

    state[2] ^= t;

    state[3] = ROTL(state[3], 11);

    return result;
}
