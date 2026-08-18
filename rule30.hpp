#pragma once

#include <x86intrin.h>
#include <cstdint>

void rule30_scalar();
void rule30_avx2();
void rule30_avx512();
void report(__m256i x, uint64_t i);
