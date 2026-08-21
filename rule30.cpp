#include "rule30.hpp"
#include <bit>
#include <cstdint>
#include <cstdio>
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

std::array<uint32_t, 5> convert_state(uint64_t a, uint64_t b, uint64_t c) {
  std::array<uint32_t, 5> retval;
  retval[4] = static_cast<uint32_t>(c);
  retval[3] = static_cast<uint32_t>(c >> 32);
  retval[2] = static_cast<uint32_t>(b >> 16);
  retval[1] = static_cast<uint32_t>(b >> 48) | static_cast<uint32_t>(a & 0xffff'0000);
  retval[0] = static_cast<uint32_t>(a >> 32);
  return retval;
}

void rule30_128() {
  puts("Performing 128 bit integer version");
  // state size is 128 bits.
  // all bits of both elements are always valid.

  uint64_t a = 0, b = 1;
  for (uint64_t i = 0;;) {
    const uint64_t next = i + 1;
    if (!(i & next))
      if (0 > printf("%4d%4d %016lx %016lx\n", std::countr_one(i),
                     b == 0xffff'ffff'ffff'ffffllu ? std::countr_one(a) + 64 : std::countr_one(b), a, b))
        std::terminate();
// second one uses two shld instructions and one or instruction.
// first one uses four shift instructions and 3 or instructions.
// on my machine shld is very slow. ymmv.
#if 1
    a ^= a << 1 | a << 2 | b >> 63 | b >> 62;
#else
    a ^= (a << 1 | b >> 63) | (a << 2 | b >> 62);
#endif
    b ^= b << 1 | b << 2;
    i = next;
  }
}

void rule30_scalar(save_state ss_func) {
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

    const uint64_t next = i + 1;
    if (!(next & interval) && ss_func)
      ss_func(i, convert_state(a, b, c));
    if (!(i & next))
      report(a, b, c, i);
  }
}
