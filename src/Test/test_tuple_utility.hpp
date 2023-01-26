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

#include <exception>
#include <iostream>
#include <tuple>
#include <utility>

#include "../AdvancedTuple.hpp"
#include "../Eprint.hpp"

namespace Test {

void test_tuple_utility() {
  using std::make_tuple;

  auto a = make_tuple(1, 2, 3, 4, 5);
  auto b = make_tuple(5, 4, 3, 2, 1);
  Eden::println_tuple(a);
  Eden::println_tuple(b);
  std::cout << a << "'s head => " << Eden::head(a) << "\n";
  std::cout << a << "'s tail => " << Eden::tail(a) << "\n";
  std::cout << a << "'s init => " << Eden::init(a) << "\n";
  std::cout << a << "'s last => " << Eden::last(a) << "\n";
  std::cout << "\n";

  auto c = make_tuple(11);
  std::cout << c << "'s head => " << Eden::head(c) << "\n";
  std::cout << c << "'s tail => " << Eden::tail(c) << "\n";
  std::cout << c << "'s init => " << Eden::init(c) << "\n";
  std::cout << c << "'s last => " << Eden::last(c) << "\n";
  std::cout << "\n";

  auto complex = make_tuple(11, "32", make_tuple(3, make_tuple(), 9), 'a');
  std::cout << complex << "'s head => " << Eden::head(complex) << "\n";
  std::cout << complex << "'s tail => " << Eden::tail(complex) << "\n";
  std::cout << complex << "'s init => " << Eden::init(complex) << "\n";
  std::cout << complex << "'s last => " << Eden::last(complex) << "\n";
  std::cout << "\n";

  auto empty = std::make_tuple();
  try {
    Eden::head(empty);
    Eden::tail(empty);
    Eden::init(empty);
    Eden::last(empty);
  } catch (const std::exception &e) {
    Eden::eprintln("Err --> {}", e.what());
  }
  std::cout << "\n";
}

}  // namespace Test