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

/**
 * @attention This file is @b DISCARDED due to `std_format_library` was found
 *
 *
 */

#pragma once

#include <utility>

#if _GLIBCXX_RELEASE >= 13

// <format> exists <=> the version of `gcc's libstdc++` is higher than 13
// (aka. _GLIBCXX_RELEASE >= 13)
#include <format>

#endif

#if __cpp_lib_format

inline namespace literals {

template <std::size_t LEN>
struct string_template {
  char str[LEN]{};
  constexpr string_template(const char (&in)[LEN]) {
    std::ranges::copy(in, str);
  };
};

template <string_template fmt_str>
constexpr auto operator""_format() {
  return [=]<typename... Args>(Args&&... args) {
    return std::format(fmt_str.str, std::forward<Args>(args)...);
  };
}
template <string_template fmt_str>
constexpr auto operator""_fmt() {
  return [=]<typename... Args>(Args&&... args) {
    return std::format(fmt_str.str, std::forward<Args>(args)...);
  };
}
template <string_template fmt_str>
constexpr auto operator""_f() {
  return [=]<typename... Args>(Args&&... args) {
    return std::format(fmt_str.str, std::forward<Args>(args)...);
  };
}

}  // namespace literals

namespace Eden {

template <typename... Args>
constexpr std::string format(const char* fmt_str, Args&&... args) {
  auto fmt_args{std::make_format_args(std::forward<Args>(args)...)};
  return std::vformat(fmt_str, fmt_args);
}

}  // namespace Eden

#else

#include <concepts>
#include <functional>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <unordered_set>
#include <vector>

#include "Concepts.hpp"

namespace Eden {

/**
 * @brief throw a `std::runtime_error` with message "lost right bracket"
 *
 */
void lost_right_bracket_exception() {
  throw std::runtime_error{"lost right bracket"};
}

/**
 * @brief throw a `std::runtime_error` with message "lost left bracket"
 *
 */
void lost_left_bracket_exception() {
  throw std::runtime_error{"lost left bracket"};
}

/**
 * @brief alias of `std::function<void(std::string &)>`
 *
 */
using to_string_lambda = std::function<void(std::string &)>;

/**
 * @brief alias of `std::function<void(std::ostringstream &)>`
 *
 */
using oss_obj_lambda = std::function<void(std::ostringstream &)>;

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
 * @brief helper of `format(fmt, args...)` (only support `{{` `}}`
 * transcription)
 *
 * @tparam Args
 * @param fmt
 * @param args_vec
 * @return std::string
 */
template <oss_obj_operative... Args>
std::string basic_format_helper(const std::string_view fmt,
                                const std::vector<oss_obj_lambda> &args_vec) {
  std::ostringstream oss{};
  oss.setf(std::ios_base::boolalpha);  // open `boolalpha` option
  std::size_t default_idx = 0;
  for (auto iter = fmt.begin(); iter != fmt.end(); ++iter) [[likely]] {
    // if could match `{{` as `{`
    bool if_left_bracket_transcription =
        *iter == '{' && std::next(iter) != fmt.end() && *std::next(iter) == '{';
    // if could match `}}` as `}`
    bool if_right_bracket_transcription =
        *iter == '}' && std::next(iter) != fmt.end() && *std::next(iter) == '}';
    // if could transcription
    bool if_bracket_transcription =
        if_left_bracket_transcription || if_right_bracket_transcription;
    // if it's a single bracket
    bool if_single_bracket = *iter == '{' || *iter == '}';
    // if it's not a arg
    bool if_not_arg = if_bracket_transcription || !if_single_bracket;
    // cases
    if (if_not_arg) [[unlikely]] {
      // 1.1 => if not transcription
      oss << *iter;
      // 1.2 => if transcription
      if (if_bracket_transcription) {
        ++iter;
      }
    } else [[likely]] {
      // possible error => missing '{'
      if (*iter == '}') [[unlikely]] {
        lost_left_bracket_exception();
      }
      // find `begin_iter` and `end_iter` of the `sign`
      auto bof_sign = iter;
      ++bof_sign;
      auto eof_sign = bof_sign;
      /**
       * @code
          while (eof_sign != fmt.end() && *eof_sign != '}') [[likely]] {
            ++eof_sign;
          }
       *
       */
      while (eof_sign != fmt.end()) [[likely]] {
        if (*eof_sign == '}') [[unlikely]] {
          if (std::next(eof_sign) != fmt.end() && *std::next(eof_sign) == '}')
              [[unlikely]] {
            ++eof_sign;
          } else [[likely]] {
            break;
          }
        } else [[likely]] {
          ++eof_sign;
        }
      }
      // possible error => missing '}'
      if (*eof_sign != '}') [[unlikely]] {
        lost_right_bracket_exception();
      }
      // update `iter` to `end_of_sign`
      iter = eof_sign;
      // now, pick the sign
      std::string_view sign{bof_sign, eof_sign};
      // two cases
      if (sign.empty()) { /* 1. {} */
        args_vec.at(default_idx)(oss);
        ++default_idx;
      } else { /* 2. {<integer>} */
        std::size_t idx = std::stoi(std::string{sign});
        args_vec.at(idx)(oss);
      }
    }
  }
  return oss.str();
}

/**
 * @brief helper of `format(fmt, args...)` (only support `{{` `}}`
 * transcription)
 *
 * @tparam Args
 * @param fmt
 * @param args_vec
 * @return std::string
 */
template <oss_obj_operative... Args>
std::string basic_format_helper(const std::string_view fmt,
                                const std::vector<to_string_lambda> &args_vec) {
  std::string result{};
  std::size_t default_idx = 0;
  for (auto iter = fmt.begin(); iter != fmt.end(); ++iter) [[likely]] {
    // if could match `{{` as `{`
    bool if_left_bracket_transcription =
        *iter == '{' && std::next(iter) != fmt.end() && *std::next(iter) == '{';
    // if could match `}}` as `}`
    bool if_right_bracket_transcription =
        *iter == '}' && std::next(iter) != fmt.end() && *std::next(iter) == '}';
    // if could transcription
    bool if_bracket_transcription =
        if_left_bracket_transcription || if_right_bracket_transcription;
    // if it's a single bracket
    bool if_single_bracket = *iter == '{' || *iter == '}';
    // if it's not a arg
    bool if_not_arg = if_bracket_transcription || !if_single_bracket;
    // cases
    if (if_not_arg) [[likely]] {
      // 1.1 => if not transcription
      result += *iter;
      // 1.2 => if transcription
      if (if_bracket_transcription) [[unlikely]] {
        ++iter;
      }
    } else [[unlikely]] {
      // possible error => missing '{'
      if (*iter == '}') [[unlikely]] {
        lost_left_bracket_exception();
      }
      // find `begin_iter` and `end_iter` of the `sign`
      auto bof_sign = iter;
      ++bof_sign;
      auto eof_sign = bof_sign;
      /**
       * @code
          while (eof_sign != fmt.end() && *eof_sign != '}') [[likely]] {
            ++eof_sign;
          }
       *
       */
      while (eof_sign != fmt.end()) [[likely]] {
        if (*eof_sign == '}') [[unlikely]] {
          if (std::next(eof_sign) != fmt.end() && *std::next(eof_sign) == '}')
              [[unlikely]] {
            ++eof_sign;
          } else [[likely]] {
            break;
          }
        } else [[likely]] {
          ++eof_sign;
        }
      }
      // possible error => missing '}'
      if (*eof_sign != '}') [[unlikely]] {
        lost_right_bracket_exception();
      }
      // update `iter` to `end_of_sign`
      iter = eof_sign;
      // now, pick the sign
      std::string_view sign{bof_sign, eof_sign};
      // two cases
      if (sign.empty()) { /* 1. {} */
        args_vec.at(default_idx)(result);
        ++default_idx;
      } else { /* 2. {<integer>} */
        std::size_t idx = std::stoi(std::string{sign});
        args_vec.at(idx)(result);
      }
    }
  }
  return result;
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
std::string could_to_string_format(const std::string_view fmt, Args &&...args) {
  auto args_vec = build_to_string_vec(std::forward<Args>(args)...);
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
std::string oss_obj_operative_format(const std::string_view fmt,
                                     Args &&...args) {
  auto args_vec = build_oss_obj_vec(std::forward<Args>(args)...);
  return basic_format_helper(fmt, std::move(args_vec));
}

/**
 * @brief return a `std::string` in `fmt` with `args` (args all satisfy
 * `string_convertible` constraint => oss_obj_operative || could_to_string)
 *
 * @tparam Args
 * @param fmt
 * @param args
 * @return std::string
 */
template <string_convertible... Args>
std::string format(const std::string_view fmt, Args &&...args) {
  if constexpr (sizeof...(args) == 0 or
                could_to_string<typename std::common_type<Args...>::type>) {
    auto args_vec = build_to_string_vec(std::forward<Args>(args)...);
    return basic_format_helper(fmt, std::move(args_vec));
  }
  auto args_vec = build_oss_obj_vec(std::forward<Args>(args)...);
  return basic_format_helper(fmt, std::move(args_vec));
}

/**
 * @brief return an empty `std::string`
 *
 * @return std::string
 */
std::string format() { return ""; }

}  // namespace Eden

#endif
