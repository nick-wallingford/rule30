#pragma once

#include <array>
#include <cstdint>
#include <string_view>
#include <x86intrin.h>

#if 0
static constexpr const uint64_t interval = 0xff'ffff'ffffllu;
#else
static constexpr const uint64_t interval = 0xfff'ffffllu;
#endif

static_assert(!((interval + 1) & interval));

typedef void (*save_state)(uint64_t, const std::array<uint32_t, 5> &);
std::array<uint32_t, 5> convert_state(__m256i);
std::array<uint32_t, 5> convert_state(uint64_t, uint64_t, uint64_t);

__m256i eval_to_vector(const char[40]);
void report(__m256i x, uint64_t i);
uint32_t string_to_hex(std::string_view);

void rule30_128();

void rule30_scalar(save_state);
void rule30_avx2(save_state);
void rule30_avx512(save_state);
void rule30_scalar(save_state, uint64_t, const char[40]);
void rule30_avx2(save_state, uint64_t, const char[40]);
void rule30_avx512(save_state, uint64_t, const char[40]);
