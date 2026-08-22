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

void certify_avx512(const attested_state *states) {
  __m512i w, x, y, z;
  w = _mm512_inserti64x4(_mm512_castsi256_si512(eval_to_vector(std::get<1>(states[0]).data())),
                         eval_to_vector(std::get<1>(states[1]).data()), 1);
  x = _mm512_inserti64x4(_mm512_castsi256_si512(eval_to_vector(std::get<1>(states[2]).data())),
                         eval_to_vector(std::get<1>(states[3]).data()), 1);
  y = _mm512_inserti64x4(_mm512_castsi256_si512(eval_to_vector(std::get<1>(states[4]).data())),
                         eval_to_vector(std::get<1>(states[5]).data()), 1);
  z = _mm512_inserti64x4(_mm512_castsi256_si512(eval_to_vector(std::get<1>(states[6]).data())),
                         eval_to_vector(std::get<1>(states[7]).data()), 1);
  const __m512i shuffle = _mm512_setr_epi32(3, 1, 5, 3, 7, 5, 6, 7, 11, 9, 13, 11, 15, 13, 14, 15);

  for (uint64_t i = (interval + 1) >> 4; i--;) {
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_ternarylogic_epi64(w, _mm512_add_epi64(w, w), _mm512_slli_epi64(w, 2), xor_or);
    x = _mm512_ternarylogic_epi64(x, _mm512_add_epi64(x, x), _mm512_slli_epi64(x, 2), xor_or);
    y = _mm512_ternarylogic_epi64(y, _mm512_add_epi64(y, y), _mm512_slli_epi64(y, 2), xor_or);
    z = _mm512_ternarylogic_epi64(z, _mm512_add_epi64(z, z), _mm512_slli_epi64(z, 2), xor_or);
    w = _mm512_permutexvar_epi32(shuffle, w);
    x = _mm512_permutexvar_epi32(shuffle, x);
    y = _mm512_permutexvar_epi32(shuffle, y);
    z = _mm512_permutexvar_epi32(shuffle, z);
  }

  std::array<__m256i, 8> results;
  results[0] = _mm512_castsi512_si256(w);
  results[1] = _mm512_extracti64x4_epi64(w, 1);
  results[2] = _mm512_castsi512_si256(x);
  results[3] = _mm512_extracti64x4_epi64(x, 1);
  results[4] = _mm512_castsi512_si256(y);
  results[5] = _mm512_extracti64x4_epi64(y, 1);
  results[6] = _mm512_castsi512_si256(z);
  results[7] = _mm512_extracti64x4_epi64(z, 1);

  __m256i shuffle2 = _mm256_set_epi32(0, 0, 0, 1, 3, 5, 7, 6);

  for (size_t i = 0; i < 8; i++) {
    std::array<uint32_t, 8> r, e;
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(r.data()), _mm256_permutevar8x32_epi32(results[i], shuffle2));
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(e.data()),
                        _mm256_permutevar8x32_epi32(eval_to_vector(std::get<2>(states[i]).data()), shuffle2));

    const auto end_index = std::get<0>(states[i]);
    const auto begin_index = end_index == interval ? 0 : end_index - interval - 1;

    bool success = true;

    for (size_t j = 0; j < 5; j++)
      if (r[j] != e[j]) {
        std::println("verification failed on interval [{},{}].", begin_index, end_index);
        success = false;
      }

    if (success)
      std::println("verified [{},{}]", begin_index, end_index);
  }
}
