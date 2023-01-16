/**
 * @file test_tuple_utility.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "../Tuple/tuple_utility.hpp"

#include <iostream>
#include <tuple>
#include <utility>

namespace Test {

void test_tuple_utility() {
  auto tuple_a = std::make_tuple(1, 2, 3, 4, 5);
  auto tuple_b = std::make_tuple(5, 4, 3, 2, 1);
  std::cout << tuple_a << " along with " << tuple_b;
  std::cout << "\n";
  Eden::println_tuple(tuple_a);
  Eden::println_tuple(tuple_b);
  std::cout << "\n";
}

} // namespace Test