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

#include "../AdvancedTuple.hpp"
#include "../Eprint.hpp"

#include <exception>
#include <iostream>
#include <tuple>
#include <utility>

namespace Test {

void test_tuple_utility() {
  auto tuple_a = std::make_tuple(1, 2, 3, 4, 5);
  auto tuple_b = std::make_tuple(5, 4, 3, 2, 1);
  Eden::println_tuple(tuple_a);
  Eden::println_tuple(tuple_b);
  std::cout << tuple_a << "'s head => " << Eden::head(tuple_a) << "\n";
  std::cout << tuple_a << "'s tail => " << Eden::tail(tuple_a) << "\n";
  std::cout << tuple_a << "'s init => " << Eden::init(tuple_a) << "\n";
  std::cout << tuple_a << "'s last => " << Eden::last(tuple_a) << "\n";
  std::cout << "\n";

  auto tuple_c = std::make_tuple(11);
  std::cout << tuple_c << "'s head => " << Eden::head(tuple_c) << "\n";
  std::cout << tuple_c << "'s tail => " << Eden::tail(tuple_c) << "\n";
  std::cout << tuple_c << "'s init => " << Eden::init(tuple_c) << "\n";
  std::cout << tuple_c << "'s last => " << Eden::last(tuple_c) << "\n";
  std::cout << "\n";

  auto complex =
      std::make_tuple(11, "32", std::make_tuple(3, std::make_tuple(), 9),
                      std::make_tuple(), 'a');
  std::cout << complex << "'s head => " << Eden::head(complex) << "\n";
  std::cout << complex << "'s tail => " << Eden::tail(complex) << "\n";
  std::cout << complex << "'s init => " << Eden::init(complex) << "\n";
  std::cout << complex << "'s last => " << Eden::last(complex) << "\n";
  std::cout << "\n";

  auto tuple_empty = std::make_tuple();
  try {
    Eden::head(tuple_empty);
    Eden::tail(tuple_empty);
    Eden::init(tuple_empty);
    Eden::last(tuple_empty);
  } catch (const std::exception &e) {
    Eden::eprintln("Err --> {}", e.what());
  }
  std::cout << "\n";
}

} // namespace Test