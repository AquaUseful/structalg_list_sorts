#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <cstdint>
#include <iterator>
#include <random>
#include <limits>

namespace fill {
  template <std::integral ValT> class Filler {
    using value_t = ValT;

    using rand_dev_t = std::random_device;
    using rand_gen_t = std::mt19937_64;
    using rand_distrib_t = std::uniform_int_distribution<value_t>;

  public:
    template <typename FwIt> inline void fill_random(FwIt first, FwIt last) {
      rand_distrib_t dist(min, max);
      std::generate(first, last, [this, &dist]() {
        return dist(m_rgen());
      });
    }

    template <typename FwIt> inline void fill_sorted(FwIt first, FwIt last) {
      reseed();
      rand_distrib_t dist(0, max_grow);
      *first = min + dist(m_rgen());
      for (auto i = first; i != std::prev(last); std::advance(i, 1)) {
        auto next = std::next(i);
        *next = *i + dist(m_rgen());
      }
    }

    template <typename FwIt> inline void fill_rev_sorted(FwIt first, FwIt last) {
      reseed();
      rand_distrib_t dist(0, max_grow);
      *first = max - dist(m_rgen());
      for (auto i = first; i != std::prev(last); std::advance(i, 1)) {
        auto next = std::next(i);
        *next = *i - dist(m_rgen());
      }
    }

    template <typename FwIt> inline void fill_partly_sorted(FwIt first, FwIt last, std::uint8_t percent) {
      auto part = std::next(first, std::distance(first, last) / 100 * percent);
      fill_sorted(first, part);
      fill_random(part, last);
    }

  private:
    inline void reseed() {
      m_rgen.seed(m_rdev());
    }

  private:
    rand_dev_t m_rdev {};
    rand_gen_t m_rgen {m_rdev()};
    static constexpr value_t min {std::numeric_limits<value_t>::min()};
    static constexpr value_t max {std::numeric_limits<value_t>::max()};
    static constexpr value_t max_grow {500};
  };
}
