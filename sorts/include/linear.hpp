#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <vector>

namespace sorts {
  template <typename FwIt, typename ItTr = std::iterator_traits<FwIt>> inline void linear(FwIt first, FwIt last) {
    if (std::distance(first, last) <= 1) {
      return;
    }
    const auto minmax = std::minmax_element(first, last);
    const auto range = *minmax.second - *minmax.first + 1;
    std::vector<std::size_t> counters(range);
    for (auto i = first; i != last; std::advance(i, 1)) {
      ++(*std::next(counters.begin(), *i - *minmax.first));
    }
    auto last_replace = first;
    for (auto i = counters.begin(); i != counters.end(); std::advance(i, 1)) {
      for (auto j = last_replace; j != std::next(last_replace, *i); std::advance(j, 1)) {
        *j = std::distance(counters.begin(), i) + *minmax.first;
      }
      last_replace = std::next(last_replace, *i);
    }
  }
}

  /*template <typename BiIt> inline void shell(BiIt first, BiIt last) {
     for (auto gap = std::distance(first, last) / 2; gap > 0; gap /= 2) {
       for (auto i = std::next(first, gap); i != last; std::advance(i, gap)) {
         for (auto j = i; j != first; std::advance(j, -gap)) {
           if (*j < *std::prev(j, gap)) {
             std::iter_swap(j, std::prev(j, gap));
           } else {
             break;
           }
         }
       }
     }
   }*/