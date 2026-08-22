#pragma once

#include <array>
#include <cstdint>
#include <filesystem>
#include <map>
#include <mutex>
#include <string_view>
#include <thread>
#include <tuple>
#include <vector>
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
// void rule30_scalar(save_state, uint64_t, const char[40]);
void rule30_avx2(save_state, uint64_t, const char[40]);
void rule30_avx512(save_state, uint64_t, const char[40]);

// end index, begin state, end state
using attested_state = std::tuple<uint64_t, std::string_view, std::string_view>;

void certify_avx512(const attested_state *); // implicitly takes 8 states
void certify_avx2(const attested_state *);   // implicitly takes 4 states
// void certify_scalar(const attested_state *);

typedef void (*certify_function)(const attested_state *);

class certifier {
  certify_function f;
  const uint8_t count_per;
  std::map<uint64_t, std::string> prestates;
  std::vector<attested_state> states;
  std::vector<std::thread> threads;

  void run();
  std::mutex m;

public:
  certifier(certify_function, uint8_t, const std::filesystem::path &);
  certifier(const certifier &) = delete;
  certifier(certifier &&) = delete;
  certifier &operator=(const certifier &) = delete;
  certifier &operator=(certifier &&) = delete;

  void wait();
};
