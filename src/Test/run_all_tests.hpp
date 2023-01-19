/**
 * @file run_all_tests.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "test_backslash.hpp"
#include "test_eprint.hpp"
#include "test_print.hpp"
#include "test_tuple_utility.hpp"

#include <functional>
#include <vector>

namespace Test {

static const std::vector<std::function<void()>> tests = {
    Test::test_print,
    // Test::test_backslash,
    Test::test_eprint,
    Test::test_tuple_utility,
};

static void IKU_IKU_IKU_AH() {
  struct EN_EN_EN_AH {
    static std::string operator()() { return "1145141919810"; }
  };
  Eden::println("{}\n", [&]() {
    std::ostringstream oss;
    oss << EN_EN_EN_AH::operator()();
    return oss.str();
  }());
}

void run_all_tests() {
  for (const auto &test : tests) {
    test();
  }
  IKU_IKU_IKU_AH();
}

} // namespace Test
