/**
 * @file test_backslash.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "../Print.hpp"
#include <string_view>

namespace Test {

void test_backslash() {
  using Eden::print;
  using Eden::println;
  std::string_view src = "Hello, World!\\{}";
  std::string_view cmp = "Hello, World!\{}";
  println("src => {}", src); // Hello, World!\{}
  println("cmp => {}", cmp); // Hello, World!{}
  for (auto &&ch : src) {
    print("{} ", ch); // H e l l o ,  W o r l d ! { }
  }
  println();
  for (auto &&ch : cmp) {
    print("{} ", ch); // H e l l o ,  W o r l d ! \ { }
  }
  println();
  println();
}

} // namespace Test
