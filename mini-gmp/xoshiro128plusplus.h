#ifndef XOSHIRO128PLUSPLUS_H
#define XOSHIRO128PLUSPLUS_H

/*  Written in 2019 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <stdint.h>

/* This is xoshiro128++ 1.0, one of our 32-bit all-purpose, rock-solid
   generators. It has excellent speed, a state size (128 bits) that is
   large enough for mild parallelism, and it passes all tests we are aware
   of.

   For generating just single-precision (i.e., 32-bit) floating-point
   numbers, xoshiro128+ is even faster.

   The state must be seeded so that it is not everywhere zero. */

typedef uint32_t xoshiro128plusplus_state[4];

#define ROTL(x, k) (((x) << (k)) | ((x) >> (32 - (k))))

void xoshiro128plusplus_seed(xoshiro128plusplus_state state, const uint32_t seed[4]);
uint32_t xoshiro128plusplus_rand32(xoshiro128plusplus_state state);

#endif  // XOSHIRO128PLUSPLUS_H
