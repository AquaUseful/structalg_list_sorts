#include <forward_list>
#include <iostream>
#include <list>

#include "linear.hpp"
#include "quick.hpp"
#include "shell.hpp"

#include "Benchmark.hpp"

int main() {

  std::forward_list<int> lst {6, 8, 2, 5, 9, 10, 444, -5, 3, -687687, 0};

  // sorts::linear(lst.begin(), lst.end());
  sorts::shell<int>(lst, lst.end());

  for (const auto& el : lst) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
  return 0;
}
