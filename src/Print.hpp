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

#include <algorithm>
#include <concepts>
#include <cstdio>
#include <format>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stdexcept>
#include <string_view>
#include <utility>
#include <vector>

#include "Concepts.hpp"
#include "Format.hpp"

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

#if __cpp_lib_format

/**
 * @brief print `fmt_str` with `args...`
 *        (use std_format_lib, support all features)
 * @tparam Args
 * @param fmt_str
 * @param args
 */
template <typename... Args>
void print(const std::string_view fmt_str, Args &&...args) {
  auto fmt_args{std::make_format_args(std::forward<Args>(args)...)};
  std::string out_str{std::vformat(fmt_str, fmt_args)};
  fputs(out_str.c_str(), stdout);
}
void print() {}

/**
 * @brief print `fmt_str` with `args...` and add a newline
 *        (use std_format_lib, support all features)
 * @tparam Args
 * @param fmt_str
 * @param args
 */
template <typename... Args>
void println(const std::string_view fmt_str, Args &&...args) {
  auto fmt_args{std::make_format_args(std::forward<Args>(args)...)};
  std::string out_str{std::vformat(fmt_str, fmt_args)};
  fputs(out_str.c_str(), stdout);
  fputs("\n", stdout);
}
void println() { fputs("\n", stdout); }

#else

/**
 * @brief print `fmt` with `args...` (by using `oss_obj_operative_format`)
 *
 * @tparam Args
 * @param fmt
 * @param args
 */
template <typename... Args>
void print(const std::string_view fmt, Args &&...args) {
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
template <typename... Args>
void println(const std::string_view fmt, Args &&...args) {
  std::cout << oss_obj_operative_format(fmt, std::forward<Args>(args)...);
  std::cout << "\n";
}
void println() { std::cout << "\n"; }

#endif

}  // namespace Eden