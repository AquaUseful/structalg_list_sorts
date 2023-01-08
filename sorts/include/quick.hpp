#pragma once

#include <algorithm>

namespace sorts {
  template <typename FwIt> inline void quick(FwIt first, FwIt last) {
    if (first == last) {
      return;
    }
    const auto pivot = *std::next(first, std::distance(first, last) / 2);
    const auto pred_lt = [&pivot](const auto& el) {
      return el < pivot;
    };
    const auto pred_nlt = [&pivot](const auto& el) {
      return !(el < pivot);
    };
    auto mid1 = std::partition(first, last, pred_lt);
    auto mid2 = std::partition(mid1, last, pred_nlt);
    quick(first, mid1);
    quick(mid2, last);
  }
}
