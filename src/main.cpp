/**
 * @file main.cpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <sstream>

#include "Test/run_all_tests.hpp"

inline void CXX_STANDARD_OUTPUT() {
  using Eden::println;
  println("C++ Standard: {}\n", __cplusplus);
}

int main(int argc, char **argv) {
  CXX_STANDARD_OUTPUT();
  Test::run_all_tests();

  return 0;
}
