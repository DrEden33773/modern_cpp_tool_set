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

#include "test_Print.hpp"
#include "test_format.hpp"
#include "test_tuple_utility.hpp"

#include <functional>
#include <vector>

namespace Test {

static const std::vector<std::function<void()>> tests = {
    // Test::test_tuple_utility,
    Test::test_Print,
    Test::test_format,
};

void run_all_tests() {
  for (const auto &test : tests) {
    test();
  }
}

} // namespace Test
