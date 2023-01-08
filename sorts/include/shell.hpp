#pragma once

#include <algorithm>
#include <cstddef>
#include <forward_list>
#include <iterator>
#include <vector>
namespace sorts {

  template <typename List, std::forward_iterator FwIt> inline void shell(List& list, FwIt last) {
    if (std::distance(list.begin(), last) <= 1) {
      return;
    }
    for (auto gap = std::distance(list.begin(), last) / 2; gap > 0; gap /= 2) {
      auto i = std::next(list.begin(), gap);
      for (std::size_t n = 1; n < std::distance(list.begin(), last) / gap; ++n, std::advance(i, gap)) {
        auto j = list.begin();
        for (std::size_t m = 0; m < n; ++m, std::advance(j, gap)) {
          if (*i < *j) {
            auto ins = j;
            auto tmp = *ins;
            *ins = *i;
            while (ins != i) {
              std::advance(ins, gap);
              std::swap(tmp, *ins);
            }
            break;
          }
        }
      }
    }
  }
}
