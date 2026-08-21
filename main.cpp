#include "rule30.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>

enum class cpu { avx512, avx2, scalar, i128 };
enum class mode { search, certify };

std::filesystem::path cert_path;

static void usage() {
  puts("usage:\n"
       "  -avx512\n"
       "  -avx2\n"
       "  -scalar\n"
       "  -128\n"
       "  -state <filename>               saves state in order for independent certification\n"
       "  -certify <filename>             checks valid certificate\n"
       "  -begin <n> <40 char hex string> skip ahead to the given state");
  std::terminate();
}

static void save_state_func(uint64_t i, const std::array<uint32_t, 5> &a) {
  std::ofstream f{cert_path, std::ios_base::app};
  const std::string s = std::format("{} {:08x}{:08x}{:08x}{:08x}{:08x}\n", i, a[0], a[1], a[2], a[3], a[4]);
  f << s;
}

int main(int c, const char **argv) {
  setbuf(stdout, NULL);
  cpu inst = cpu::scalar;
  mode m = mode::search;
  save_state f = nullptr;
  int64_t begin = 0;
  const char *begin_state = nullptr;

  if (__builtin_cpu_supports("x86-64-v4"))
    inst = cpu::avx512;
  else if (__builtin_cpu_supports("x86-64-v3"))
    inst = cpu::avx2;

  for (int i = 1; i < c; i++)
    if (!strcmp(argv[i], "-avx2"))
      inst = cpu::avx2;
    else if (!strcmp(argv[i], "-avx512"))
      inst = cpu::avx512;
    else if (!strcmp(argv[i], "-scalar"))
      inst = cpu::scalar;
    else if (!strcmp(argv[i], "-128"))
      inst = cpu::i128;
    else if (!strcmp(argv[i], "-state") && ++i < c) {
      m = mode::search;
      cert_path = argv[i];
      f = save_state_func;
    } else if (!strcmp(argv[i], "-certify") && ++i < c) {
      m = mode::certify;
      cert_path = argv[i];
    } else if (!strcmp(argv[i], "-begin") && i + 2 < c) {
      begin = std::atoll(argv[i + 1]);
      begin_state = argv[i + 2];

      if (strlen(begin_state) != 40) {
        puts("invalid state. must be 40 digits.");
        return 2;
      }
      for (const char *x = begin_state; *x; ++x)
        if (!(('0' <= *x && *x <= '9') || ('a' <= *x && *x <= 'f') || ('A' <= *x && *x <= 'F'))) {
          puts("invalid state. must be hexadecimal.");
          return 3;
        }

      if (begin <= 0) {
        puts("invalid starting point.");
        return 4;
      }

      i += 2;
    } else
      usage();

  if (m == mode::search) {
    if (begin)
      switch (inst) {
      case cpu::avx512:
        rule30_avx512(f, begin, begin_state);
        break;
      case cpu::avx2:
        rule30_avx2(f, begin, begin_state);
        break;
      case cpu::scalar:
        rule30_scalar(f, begin, begin_state);
        break;
      case cpu::i128:
        puts("i128 mode cannot specify begin state");
        return 5;
      }
    else
      switch (inst) {
      case cpu::avx512:
        rule30_avx512(f);
        break;
      case cpu::avx2:
        rule30_avx2(f);
        break;
      case cpu::scalar:
        rule30_scalar(f);
        break;
      case cpu::i128:
        if (f) {
          puts("i128 mode cannot store states");
          return 1;
        }
        rule30_128();
      }
  } else {
    puts("unimplemented");
    return 6;
  }

  return 0;
}
