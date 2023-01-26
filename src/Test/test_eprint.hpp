/**
 * @file test_eprint.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <exception>
#include <vector>

#include "../Eprint.hpp"
#include "../Print.hpp"

namespace Test {

void test_eprint() {
  std::vector<int> arr{1, 2, 3, 4, 5};
  try {
    Eden::println("{}", arr.at(10));
  } catch (const std::exception &err) {
    Eden::eprintln("Error --> {}", err.what());
  }
  Eden::println();
}

}  // namespace Test