#include "rule30.hpp"
#include <cstdio>

static constexpr int xor_or_or = _MM_TERNLOG_A ^ (_MM_TERNLOG_B | _MM_TERNLOG_C);

void rule30_avx512() {
  puts("Performing AVX512 version");
  __m256i x = _mm256_setr_epi64x(0, 0, 0, 1);
  report(x, 0);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  report(x, 1);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  report(x, 3);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  report(x, 7);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
  report(x, 15);

  const __m256i shuffle = _mm256_setr_epi32(3, 1, 5, 3, 7, 5, 6, 7);

  for (uint64_t i = 15;;) {
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_ternarylogic_epi64(x, _mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2), xor_or_or);
    x = _mm256_permutevar8x32_epi32(x, shuffle);
    i += 16;
    if (!(i & (i + 1)))
      report(x, i);
  }
}
