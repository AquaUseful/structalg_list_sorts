#pragma once

#include <chrono>

class Timer {
public:
  using clock_t = std::chrono::high_resolution_clock;
  using duration_t = std::chrono::microseconds;

public:
  template <typename FuncT, typename... Args> static constexpr duration_t measure(const FuncT func, Args... args) {
    const auto start = m_clock.now();
    func(args...);
    const auto end = m_clock.now();
    return std::chrono::duration_cast<duration_t>(end - start);
  }

private:
  constexpr static clock_t m_clock {};
};
