/**
 * @file Format.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-17
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

namespace Eden {

using to_string_lambda = std::function<void(std::string &)>;

/**
 * @brief build a vector of `to_string_lambda` from `args`
 *
 * @tparam Args
 * @param args
 * @return std::vector<to_string_lambda>
 */
template <string_convertible... Args>
auto build_fmt_args_vec(Args &&...args) -> std::vector<to_string_lambda> {
  return {[&args](std::string &str) {
    str += std::to_string(std::forward<Args>(args));
  }...};
}

/**
 * @brief helper of `format(fmt, args...)`
 *
 * @tparam Args
 * @param fmt
 * @param args_vec
 * @return std::string
 */
template <string_convertible... Args>
std::string format_helper(std::string_view fmt,
                          const std::vector<to_string_lambda> &args_vec) {
  std::string result{};
  std::size_t default_idx = 0;
  auto iter = fmt.begin();
  while (iter != fmt.end()) {
    if (*iter != '{' && *iter != '}') {
      result += *iter;
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
        args_vec[default_idx](result);
        ++default_idx;
      } else { /* 2. {<integer>} */
        std::size_t idx = std::stoi(std::string{sign});
        args_vec[idx](result);
        // recommend: update `default_idx` to `idx`
        default_idx = idx;
      }
    }
    // update `iter`
    ++iter;
  }
  return result;
}

/**
 * @brief return a `std::string` in `fmt` with `args`
 *
 * @tparam Args
 * @param fmt
 * @param args
 * @return std::string
 */
template <string_convertible... Args>
std::string format(std::string_view fmt, Args &&...args) {
  return format_helper(fmt, build_fmt_args_vec(std::forward<Args>(args)...));
}
template <typename... Args> std::string format() { return ""; }

} // namespace Eden