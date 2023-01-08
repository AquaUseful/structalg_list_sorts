#pragma once

#include <algorithm>

namespace sorts {
  template <std::forward_iterator FwIt, typename ItTr = std::iterator_traits<FwIt>> inline void quick(FwIt first, FwIt& last) {
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
    quick<FwIt, ItTr>(first, mid1);
    quick<FwIt, ItTr>(mid2, last);
  }
}
