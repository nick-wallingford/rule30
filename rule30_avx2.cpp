#include "rule30.hpp"
#include <array>
#include <bit>
#include <cstdio>
#include <exception>

void report(__m256i x, uint64_t i) {
  std::array<uint32_t, 8> a;
  _mm256_storeu_si256(reinterpret_cast<__m256i *>(a.data()), x);
  int n;
  if (a[6] != 0xffff'ffff)
    n = std::countr_one(a[6]);
  else if (a[7] != 0xffff'ffff)
    n = std::countr_one(a[7]) + 32;
  else if (a[5] != 0xffff'ffff)
    n = std::countr_one(a[5]) + 64;
  else if (a[3] != 0xffff'ffff)
    n = std::countr_one(a[3]) + 96;
  else
    n = std::countr_one(a[1]) + 128;
  if (0 > printf("%4d%4d %08x %08x %08x %08x %08x\n", std::countr_one(i), n, a[1], a[3], a[5], a[7], a[6]))
    std::terminate();
}

void rule30_avx2() {
  puts("Performing AVX2 version");
  __m256i x = _mm256_setr_epi64x(0, 0, 0, 1);
  report(x, 0);
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  report(x, 1);
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  report(x, 3);
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  report(x, 7);
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
  report(x, 15);

  const __m256i shuffle = _mm256_setr_epi32(3, 1, 5, 3, 7, 5, 6, 7);

  for (uint64_t i = 15;;) {
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_xor_si256(x, _mm256_or_si256(_mm256_add_epi64(x, x), _mm256_slli_epi64(x, 2)));
    x = _mm256_permutevar8x32_epi32(x, shuffle);
    i += 16;
    if (!(i & (i + 1)))
      report(x, i);
  }
}
