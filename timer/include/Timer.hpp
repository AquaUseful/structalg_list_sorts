#pragma once

#include <chrono>

class Timer {
public:
  using clock_t = std::chrono::high_resolution_clock;
  using duration_t = std::chrono::microseconds;

  template <typename ReturnT> struct Measure {
    duration_t duration;
    ReturnT func_result;
  };

public:
  template <typename FuncT, typename... Args>
  static constexpr auto measure(const FuncT func, Args... args) -> Measure<decltype(func(args...))> {
    const auto start = m_clock.now();
    const auto func_result = func(args...);
    const auto end = m_clock.now();
    return Measure<decltype(func(args...))> {std::chrono::duration_cast<duration_t>(end - start), func_result};
  }

private:
  constexpr static clock_t m_clock {};
};
