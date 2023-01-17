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
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Eden {

using to_string_lambda = std::function<void(std::string &)>;
using oss_obj_lambda = std::function<void(std::ostringstream &)>;

#define TO_STRING_LAMBDA_CAPTURE_REF(target, arg)                              \
  [&] { (target) += std::to_string(arg); }

#define OSS_OBJ_LAMBDA_CAPTURE_REF(target, arg) [&] { (target) << (arg); }

/**
 * @brief build a vector of `to_string_lambda` from `args`
 *
 * @tparam Args
 * @param args
 * @return std::vector<to_string_lambda>
 */
template <could_to_string... Args>
auto build_to_string_vec(Args &&...args) -> std::vector<to_string_lambda> {
  return {[&args](std::string &str) {
    str += std::to_string(std::forward<Args>(args));
  }...};
}

/**
 * @brief build a vector of `oss_obj_lambda` from `args`
 *
 * @tparam Args
 * @param args
 * @return std::vector<oss_obj_lambda>
 */
template <oss_obj_operative... Args>
auto build_oss_obj_vec(Args &&...args) -> std::vector<oss_obj_lambda> {
  return {[&args](std::ostringstream &oss) { oss << args; }...};
}

/**
 * @brief helper of `format(fmt, args...)` (doesn't support `{{` `}}`
 * transcription and more format options )
 *
 * @tparam Args
 * @param fmt
 * @param args_vec
 * @return std::string
 */
template <could_to_string... Args>
std::string basic_format_helper(std::string_view fmt,
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
      }
    }
    // update `iter`
    ++iter;
  }
  return result;
}

/**
 * @brief helper of `format(fmt, args...)` (doesn't support `{{` `}}`
 * transcription and more format options )
 *
 * @tparam Args
 * @param fmt
 * @param args_vec
 * @return std::string
 */
template <oss_obj_operative... Args>
std::string basic_format_helper(std::string_view fmt,
                                const std::vector<oss_obj_lambda> &args_vec) {
  std::ostringstream oss{};
  oss.setf(std::ios_base::boolalpha); // open `boolalpha` option
  std::size_t default_idx = 0;
  auto iter = fmt.begin();
  while (iter != fmt.end()) {
    if (*iter != '{' && *iter != '}') {
      oss << *iter;
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
        args_vec[default_idx](oss);
        ++default_idx;
      } else { /* 2. {<integer>} */
        std::size_t idx = std::stoi(std::string{sign});
        args_vec[idx](oss);
      }
    }
    // update `iter`
    ++iter;
  }
  return oss.str();
}

/**
 * @brief return a `std::string` in `fmt` with `args` (args all satisfy
 * `could_to_string` constraint)
 *
 * @tparam Args
 * @param fmt
 * @param args
 * @return std::string
 */
template <could_to_string... Args>
std::string format(std::string_view fmt, Args &&...args) {
  auto args_vec = build_to_string_vec(std::forward<Args>(args)...);
  return basic_format_helper(fmt, std::move(args_vec));
}

/**
 * @brief return a `std::string` in `fmt` with `args` (args all satisfy
 * `could_to_string` constraint) => only used for `Print(fmt, args...)`
 *
 * @tparam Args
 * @param fmt
 * @param args
 * @return std::string
 */
template <could_to_string... Args>
std::string could_to_string_format(std::string_view fmt, Args &&...args) {
  auto args_vec = build_to_string_vec(std::forward<Args>(args)...);
  return basic_format_helper(fmt, std::move(args_vec));
}

/**
 * @brief return a `std::string` in `fmt` with `args` (args all satisfy
 * `oss_obj_operative` constraint)
 *
 * @tparam Args
 * @param fmt
 * @param args
 * @return std::string
 */
template <oss_obj_operative... Args>
std::string format(std::string_view fmt, Args &&...args) {
  auto args_vec = build_oss_obj_vec(std::forward<Args>(args)...);
  return basic_format_helper(fmt, std::move(args_vec));
}

/**
 * @brief return a `std::string` in `fmt` with `args` (args all satisfy
 * `oss_obj_operative` constraint) => only used for `Print(fmt, args...)`
 *
 * @tparam Args
 * @param fmt
 * @param args
 * @return std::string
 */
template <oss_obj_operative... Args>
std::string oss_obj_operative_format(std::string_view fmt, Args &&...args) {
  auto args_vec = build_oss_obj_vec(std::forward<Args>(args)...);
  return basic_format_helper(fmt, std::move(args_vec));
}

/**
 * @brief return an empty `std::string`
 *
 * @return std::string
 */
std::string format() { return ""; }

} // namespace Eden