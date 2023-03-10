/**
 * @file test_format.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-17
 *
 * @copyright Copyright (c) 2023
 *
 */

/**
 * @attention This file is @b DISCARDED due to `std_format_library` was found
 * So of course, the `eden_format_library` will be deprecated
 *
 */

#pragma once

#include <cassert>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

#include "../AdvancedPair.hpp"
#include "../AdvancedTuple.hpp"
#include "../Format.hpp"
#include "../Print.hpp"

namespace Test {

void test_format() {
  using Eden::format;
  using Eden::println;

  std::string tuple_str = Eden::format("{}", std::make_tuple(1, 2));
  std::string pair_str = Eden::format("{}", std::make_pair(1, 2));

  println("tuple => {}", std::make_tuple(1, 2));
  println(" pair => {}", std::make_pair(1, 2));
  println();
  println("Eden::format(tuple) => {}", tuple_str);
  println(" Eden::format(pair) => {}", pair_str);
  println();

  assert(tuple_str == pair_str);
  println("format(tuple) == format(pair)");
  println();

  println("`test_format()` passed!");
  println();
}

}  // namespace Test