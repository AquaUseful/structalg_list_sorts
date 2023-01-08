#include <cstdint>
#include <forward_list>
#include <iostream>
#include <list>

#include "Filler.hpp"
#include "linear.hpp"
#include "quick.hpp"
#include "shell.hpp"

#include "Benchmark.hpp"

int main() {

  std::forward_list<std::int32_t> lst;
  lst.resize(100);

  fill::Filler<std::int32_t> filler;
  filler.fill_random(lst.begin(), lst.end());

  benchmark::Benchmark<std::forward_list<int>> bench {100};

  for (const auto& el : lst) {
    std::cout << el << ' ';
  }

  std::cout << '\n';

  bench.resize(100);
  bench.fill_random();
  auto res = bench.measure(100);
  // sorts::linear(lst.begin(), lst.end());
  // sorts::quick(lst.begin(), lst.end());
  // sorts::shell(lst, lst.end());

  std::cout << res.quick_time;
  // for (const auto& el : lst) {
  //   std::cout << el << ' ';
  // }
  std::cout << '\n';
  return 0;
}
