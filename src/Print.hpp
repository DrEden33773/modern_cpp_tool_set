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

#include <concepts>
#include <functional>
#include <iostream>
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
 * @brief helper of `print(fmt, tuple<args...>)`
 * @warning @b cannot_use!
 * @tparam Args
 * @param fmt
 * @param args_tuple
 */
template <printable... Args>
constexpr void print_helper(std::string_view fmt,
                            const std::tuple<Args...> &args_tuple) {
  throw std::runtime_error(
      "Cannot use, because I haven't implemented run-time tuple indexer");

  std::cout << std::boolalpha;

  std::size_t default_idx = 0;
  auto iter = fmt.begin();
  while (iter != fmt.end()) {
    if (*iter != '{' && *iter != '}') {
      std::cout << *iter;
    } else if (*iter == '{') {
      // find `begin_iter` and `end_iter` of the `sign`
      auto beg_of_sign = iter;
      ++beg_of_sign;
      auto end_of_sign = beg_of_sign;
      while (end_of_sign != fmt.end() && *end_of_sign != '}') {
        ++end_of_sign;
      }
      // update `iter` to `end_of_sign`
      iter = end_of_sign;
      // now, pick the sign
      std::string_view sign{beg_of_sign, end_of_sign};
      // two cases
      if (sign.empty()) { /* 1. {} */
        std::cout << get_tuple_value(default_idx, args_tuple);
        ++default_idx;
      } else { /* 2. {<integer>} */
        std::size_t idx = std::stoi(std::string{sign});
        std::cout << get_tuple_value(idx, args_tuple);
        // recommend: update `default_idx` to `idx`
        default_idx = idx;
      }
    }
    // update `iter`
    ++iter;
  }
}

using cout_lambda = std::function<void()>;

template <printable... Args>
constexpr auto build_print_args_vec(Args &&...args) {
  return std::vector<cout_lambda>{[&args]() { std::cout << args; }...};
}

template <printable... Args>
constexpr void print_helper(std::string_view fmt,
                            const std::vector<cout_lambda> &args_vec) {
  std::cout << std::boolalpha;

  std::size_t default_idx = 0;
  auto iter = fmt.begin();
  while (iter != fmt.end()) {
    if (*iter != '{' && *iter != '}') {
      std::cout << *iter;
    } else if (*iter == '{') {
      // find `begin_iter` and `end_iter` of the `sign`
      auto beg_of_sign = iter;
      ++beg_of_sign;
      auto end_of_sign = beg_of_sign;
      while (end_of_sign != fmt.end() && *end_of_sign != '}') {
        ++end_of_sign;
      }
      // update `iter` to `end_of_sign`
      iter = end_of_sign;
      // now, pick the sign
      std::string_view sign{beg_of_sign, end_of_sign};
      // two cases
      if (sign.empty()) { /* 1. {} */
        args_vec[default_idx]();
        ++default_idx;
      } else { /* 2. {<integer>} */
        std::size_t idx = std::stoi(std::string{sign});
        args_vec[idx]();
        // recommend: update `default_idx` to `idx`
        default_idx = idx;
      }
    }
    // update `iter`
    ++iter;
  }
}

/**
 * @brief print `fmt` with `args...`
 *
 * @tparam Args
 * @param fmt
 * @param args
 */
template <printable... Args>
constexpr void print(std::string_view fmt, Args &&...args) {
  print_helper(fmt, build_print_args_vec(std::forward<Args>(args)...));
}
template <typename... Args> constexpr void print() {}

/**
 * @brief print `fmt` with `args...` and a newline
 *
 * @tparam Args
 * @param fmt
 * @param args
 */
template <printable... Args>
constexpr void println(std::string_view fmt, Args &&...args) {
  print_helper(fmt, build_print_args_vec(std::forward<Args>(args)...));
  std::cout << "\n";
}
template <typename... Args> constexpr void println() { std::cout << "\n"; }

} // namespace Eden