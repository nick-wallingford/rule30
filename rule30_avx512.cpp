#include "rule30.hpp"
#include <cstdio>
#include <print>

static constexpr int xor_or = _MM_TERNLOG_A ^ (_MM_TERNLOG_B | _MM_TERNLOG_C);

static void __attribute__((noinline)) rule30_avx512(save_state ss_func, uint64_t i, __m256i x) {
  const __m256i shuffle = _mm256_setr_epi32(3, 1, 5, 3, 7, 5, 6, 7);

  for (;;) {
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
    x = _mm256_permutevar8x32_epi32(x, shuffle);
    i += 16;

    const uint64_t next = i + 1;
    if (!(next & interval) && ss_func) [[unlikely]]
      ss_func(i, convert_state(x));
    if (!(i & next)) [[unlikely]]
      report(x, i);
  }
}

void rule30_avx512(save_state ss_func) {
  puts("Performing AVX512 version");
  __m256i x = _mm256_setr_epi64x(0, 0, 0, 1);
  report(x, 0);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  report(x, 1);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  report(x, 3);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  report(x, 7);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or);
  report(x, 15);

  rule30_avx512(ss_func, 15, x);
}

void rule30_avx512(save_state ss_func, uint64_t i, const char s[40]) {
  if (interval != (i & interval)) {
    std::println("initial state must be of the form {} * k - 1", interval);
    std::terminate();
  }
  puts("Performing AVX512 version");
  rule30_avx512(ss_func, i, eval_to_vector(s));
}
