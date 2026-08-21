#include "rule30.hpp"
#include <array>
#include <bit>
#include <charconv>
#include <cstdio>
#include <exception>
#include <iostream>

void __attribute__((noinline)) report(__m256i x, uint64_t i) {
  std::array<uint32_t, 8> a;
  x = _mm256_permutevar8x32_epi32(x, _mm256_set_epi32(0, 0, 0, 1, 3, 5, 7, 6));
  _mm256_storeu_si256(reinterpret_cast<__m256i *>(a.data()), x);
  int n = 0;
  for (auto y : a)
    if (y == 0xffff'ffff)
      n += 32;
    else {
      n += std::countr_one(y);
      break;
    }
  if (0 > printf("%4d%4d %08x %08x %08x %08x %08x\n", std::countr_one(i), n, a[4], a[3], a[2], a[1], a[0]))
    std::terminate();
}

std::array<uint32_t, 5> __attribute__((noinline)) convert_state(__m256i x) {
  std::array<uint32_t, 5> r;
  x = _mm256_permutevar8x32_epi32(x, _mm256_setr_epi32(1, 3, 5, 7, 6, 0, 0, 0));
  const __m256i mask = _mm256_setr_epi32(-1, -1, -1, -1, -1, 0, 0, 0);
  _mm256_maskstore_epi32(reinterpret_cast<int32_t *>(r.data()), mask, x);
  return r;
}

__m256i __attribute__((noinline)) eval_to_vector(const char *s) {
  std::array<int32_t, 5> a;
  for (size_t i = 0; i < 5; i++, s += 8)
    a[i] = string_to_hex({s, 8});
  return _mm256_setr_epi32(a[1], a[0], a[2], a[1], a[3], a[2], a[4], a[3]);
}

static void __attribute__((noinline)) rule30_avx2(save_state ss_func, uint64_t i, __m256i x) {
  const __m256i shuffle = _mm256_setr_epi32(3, 1, 5, 3, 7, 5, 6, 7);

  for (;;) {
    // update elements.
    // these 16 lines updates the upper 32 bit of all 4 elements
    // and the lower 32 bits of the final element.
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
    // reconstitute.
    // this fixes the lower 32 bits of the first three elements.
    x = _mm256_permutevar8x32_epi32(x, shuffle);
    i += 16;
    const uint64_t next = i + 1;
    if (!(next & interval) && ss_func) [[unlikely]]
      ss_func(i, convert_state(x));
    if (!(i & next)) [[unlikely]]
      report(x, i);
  }
}

void rule30_avx2(save_state ss_func) {
  puts("Performing AVX2 version");
  // state size is 160 bits.
  // first three elements are only valid for upper 32 bits.
  // final element is valid for all 64 bits.
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

  rule30_avx2(ss_func, 15, x);
}

void rule30_avx2(save_state ss_func, uint64_t i, const char s[40]) {
  puts("Performing AVX2 version");
  rule30_avx2(ss_func, i, eval_to_vector(s));
}
