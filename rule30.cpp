#include "rule30.hpp"
#include <bit>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <exception>

static void report(uint64_t a, uint64_t b, uint64_t c, uint64_t i) {
  int n;
  b >>= 16;
  a >>= 16;
  if (c != 0xffff'ffff'ffff'ffffllu)
    n = std::countr_one(c);
  else if (b != 0xffff'ffff'ffffllu)
    n = std::countr_one(b) + 64;
  else
    n = std::countr_one(a) + 64 + 48;

  if (0 > printf("%4d%4d %012lx %012lx %016lx\n", std::countr_one(i), n, a, b, c))
    std::terminate();
}

void rule30_scalar() {
  puts("Performing scalar version");
  // state size is 160 bits.
  // all 64 bits of c are always valid.
  // upper 48 bits of a and b are always valid.
  // lower 16 bits of a and b are only valid between reconstitute and DO steps
  uint64_t a = 0, b = 0, c = 1;
  report(a, b, c, 0);
  a ^= a << 1 | a << 2;
  b ^= b << 1 | b << 2;
  c ^= c << 1 | c << 2;
  report(a, b, c, 1);
  a ^= a << 1 | a << 2;
  b ^= b << 1 | b << 2;
  c ^= c << 1 | c << 2;
  a ^= a << 1 | a << 2;
  b ^= b << 1 | b << 2;
  c ^= c << 1 | c << 2;
  report(a, b, c, 3);
  a ^= a << 1 | a << 2;
  b ^= b << 1 | b << 2;
  c ^= c << 1 | c << 2;
  a ^= a << 1 | a << 2;
  b ^= b << 1 | b << 2;
  c ^= c << 1 | c << 2;
  a ^= a << 1 | a << 2;
  b ^= b << 1 | b << 2;
  c ^= c << 1 | c << 2;
  a ^= a << 1 | a << 2;
  b ^= b << 1 | b << 2;
  c ^= c << 1 | c << 2;
  report(a, b, c, 7);

  for (uint64_t i = 7;;) {
    // update.
    // this invalidates lower 16 bits of a and b.
    a ^= a << 1 | a << 2;
    b ^= b << 1 | b << 2;
    c ^= c << 1 | c << 2;
    a ^= a << 1 | a << 2;
    b ^= b << 1 | b << 2;
    c ^= c << 1 | c << 2;
    a ^= a << 1 | a << 2;
    b ^= b << 1 | b << 2;
    c ^= c << 1 | c << 2;
    a ^= a << 1 | a << 2;
    b ^= b << 1 | b << 2;
    c ^= c << 1 | c << 2;
    a ^= a << 1 | a << 2;
    b ^= b << 1 | b << 2;
    c ^= c << 1 | c << 2;
    a ^= a << 1 | a << 2;
    b ^= b << 1 | b << 2;
    c ^= c << 1 | c << 2;
    a ^= a << 1 | a << 2;
    b ^= b << 1 | b << 2;
    c ^= c << 1 | c << 2;
    a ^= a << 1 | a << 2;
    b ^= b << 1 | b << 2;
    c ^= c << 1 | c << 2;

    // reconstitute.
    // this revalidates the lower 16 bits of a and b.
    a &= 0xffff'ffff'ffff'0000llu;
    a |= b >> 48;
    b &= 0xffff'ffff'ffff'0000llu;
    b |= c >> 48;

    i += 8;

    if (!(i & (i + 1)))
      report(a, b, c, i);
  }
}

int main(int c, char **argv) {
  setbuf(stdout, NULL);
  if (c > 1)
    if (!strcmp(argv[1], "-avx2"))
      rule30_avx2();
    else if (!strcmp(argv[1], "-avx512"))
      rule30_avx512();
    else if (!strcmp(argv[1], "-scalar"))
      rule30_scalar();
    else
      puts("options:\n  -avx512\n  -avx2\n  -scalar");
  else if (__builtin_cpu_supports("x86-64-v4"))
    rule30_avx512();
  else if (__builtin_cpu_supports("x86-64-v3"))
    rule30_avx2();
  else
    rule30_scalar();
}
