#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <random>
#include <vector>
#include <chrono>

#include "Timer.hpp"
#include "Filler.hpp"
#include "linear.hpp"
#include "quick.hpp"
#include "shell.hpp"

namespace benchmark {
  template <typename Container> class Benchmark {
  public:
    using timer_t = Timer;

    using measurement_t = struct Measurement {
      timer_t::duration_t linear_time;
      timer_t::duration_t quick_time;
      timer_t::duration_t shell_time;
    };

    using cont_t = Container;
    using filler_t = fill::Filler<typename Container::value_type>;

  public:
    Benchmark(std::size_t size) {
      m_container.resize(size);
    }

    void resize(std::size_t size) {
      m_container.resize(size);
    }

    void fill_random() {
      m_filler.fill_random(m_container.begin(), m_container.end());
    }

    void fill_sorted() {
      m_filler.fill_sorted(m_container.begin(), m_container.end());
    }

    void fill_rev_sorted() {
      m_filler.fill_rev_sorted(m_container.begin(), m_container.end());
    }

    void fill_partly_sorted(std::uint8_t percent) {
      m_filler.fill_partly_sorted(m_container.begin(), m_container.end(), percent);
    }

    measurement_t measure(std::uint8_t percent) {

      measurement_t result {};
      measure_linear(percent, result);
      measure_quick(percent, result);
      measure_shell(percent, result);
      return result;
    };

  private:
    inline void measure_linear(const std::uint8_t percent, measurement_t& result) {
      auto copy = m_container;
      auto part = std::next(copy.begin(), std::distance(copy.begin(), copy.end()) / 100 * percent);
      result.linear_time = timer_t::measure(sorts::linear<typename cont_t::iterator>, copy.begin(), part);
    }

    inline void measure_quick(const std::uint8_t percent, measurement_t& result) {
      auto copy = m_container;
      auto part = std::next(copy.begin(), std::distance(copy.begin(), copy.end()) / 100 * percent);
      result.quick_time = timer_t::measure(sorts::quick<typename cont_t::iterator>, copy.begin(), part);
    }

    inline void measure_shell(const std::uint8_t percent, measurement_t& result) {
      auto copy = m_container;
      auto part = std::next(copy.begin(), std::distance(copy.begin(), copy.end()) / 100 * percent);
      result.shell_time = timer_t::measure(sorts::shell<cont_t, typename cont_t::iterator>, copy, copy.end());
    }

  private:
    cont_t m_container {};
    filler_t m_filler;
    // static constexpr std::size_t repeats {1000};
  };
}
