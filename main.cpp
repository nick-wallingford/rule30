#include "rule30.hpp"
#include <cstdio>
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
       "  -state <filename>          saves state in order for independent certification\n"
       "  -certify <filename>        checks valid certificate");
  std::terminate();
}

static void save_state_func(uint64_t i, const std::array<uint32_t, 5> &a) {
  std::ofstream f{cert_path, std::ios_base::app};
  const std::string s = std::format("{} {:08x}{:08x}{:08x}{:08x}{:08x}\n", i, a[0], a[1], a[2], a[3], a[4]);
  f << s;
}

int main(int c, char **argv) {
  setbuf(stdout, NULL);
  cpu inst = cpu::scalar;
  mode m = mode::search;
  save_state f = nullptr;

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
    } else
      usage();

  if (m == mode::search)
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
}
