#include "rule30.hpp"
#include <fstream>
#include <map>
#include <print>

certifier::certifier(certify_function f, uint8_t n, const std::filesystem::path &p) : f{f}, count_per{n} {
  if (n != 4 && n != 8) {
    puts("count must be 4 or 8");
    std::terminate();
  }

  std::ifstream file{p};

  for (std::string line; std::getline(file, line);) {
    if (line.size() < 42 || line[line.size() - 41] != ' ') {
      std::println("invalid line: {}", line);
      std::terminate();
    }

    uint64_t x{};
    if (const auto [ptr, ec] = std::from_chars(line.data(), line.data() + line.size() - 41, x); ec != std::errc{}) {
      std::println("invalid line: {}", line);
      std::terminate();
    }

    std::string_view sv{line.data() + line.size() - 40, 40};
    prestates.emplace(x, sv);
  }

  if (prestates.empty()) {
    std::println("empty file");
    std::terminate();
  }

  uint64_t prev = std::numeric_limits<uint64_t>::max();
  static constexpr std::string_view pre_initial_state{"ffffffffffffffffffffffffffffffffffffffff"};
  states.reserve(prestates.size());

  for (const auto &[x, s] : prestates) {
    states.emplace_back(x, states.empty() ? pre_initial_state : std::get<2>(states.back()), s);
    uint64_t gap = x - prev;
    if (gap != interval + 1) {
      std::println("incorrect gap between {} and {}. Gap is {}, must be {}.", prev, x, gap, interval + 1);
      std::terminate();
    }
    if (!(x & (x + 1))) {
      uint64_t value = 0;
      for (size_t i = 40; i--;)
        if (s[i] == 'f' || s[i] == 'F')
          value += 4;
        else {
          uint8_t x = s[i];
          if ('0' <= x && x <= '9')
            x ^= '0';
          else if ('a' <= x && x <= 'f')
            x -= 'a' - 10;
          else if ('A' <= x && x <= 'F')
            x -= 'A' - 10;

          for (; x & 1; x >>= 1)
            ++value;
          break;
        }
      std::println("cert file attests {} {}", std::countr_one(x), value);
    }
    prev = x;
  }

  threads.reserve(std::thread::hardware_concurrency());

  for (uint64_t i = threads.capacity(); i--;)
    threads.emplace_back([this]() { run(); });
}

void certifier::run() {
  for (;;) {
    std::unique_lock lock{m};
    if (states.empty())
      return;

    std::array<attested_state, 8> a;
    for (uint8_t i = 0; i < count_per; i++)
      if (states.empty())
        a[i] = a[i - 1];
      else {
        a[i] = states.back();
        states.pop_back();
      }

    lock.unlock();
    f(a.data());
  }
}

void certifier::wait() {
  for (auto &t : threads)
    t.join();
}
