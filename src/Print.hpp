/**
 * @file Print.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "Concepts.hpp"
#include "Format.hpp"

#include <algorithm>
#include <concepts>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stdexcept>
#include <string_view>
#include <utility>
#include <vector>

// print("{}", 1);
//   => 1
// print("{}, {}", 1, 2);
//   => 1, 2
// print("{1}, {0}", 1, 2);
//   => 2, 1
// print("{1}, {0}, {}", 1, 2);
//   => 2, 1, 1
// print("{0}, {}, {1}, {}", 1, 2);
//   => 1, 1, 2, 2

namespace Eden {

/**
 * @brief same as `std::make_tuple`
 *
 * @tparam Args
 * @param args
 * @return std::tuple<Args...>
 */
template <typename... Args>
constexpr auto into_tuple(Args &&...args) -> std::tuple<Args...> {
  return std::make_tuple(std::forward<Args>(args)...);
}

/**
 * @brief print `fmt` with `args...` (by using `oss_obj_operative_format`)
 *
 * @tparam Args
 * @param fmt
 * @param args
 */
template <printable... Args> void print(std::string_view fmt, Args &&...args) {
  std::cout << oss_obj_operative_format(fmt, std::forward<Args>(args)...);
}
void print() {}

/**
 * @brief print `fmt` with `args...` and a newline (by using
 * `oss_obj_operative_format`)
 *
 * @tparam Args
 * @param fmt
 * @param args
 */
template <printable... Args>
void println(std::string_view fmt, Args &&...args) {
  std::cout << oss_obj_operative_format(fmt, std::forward<Args>(args)...);
  std::cout << "\n";
}
void println() { std::cout << "\n"; }

} // namespace Eden