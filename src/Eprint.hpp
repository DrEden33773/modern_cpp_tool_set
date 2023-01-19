/**
 * @file Eprint.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "Format.hpp"

#include <cstdio>
#include <format>

namespace Eden {
#if __cpp_lib_format

/**
 * @brief print error message to `stderr`
 *
 * @tparam Args
 * @param fmt_str
 * @param args
 */
template <string_convertible... Args>
void eprint(const std::string_view fmt_str, Args &&...args) {
  auto fmt_args{std::make_format_args(std::forward<Args>(args)...)};
  std::string out_str{std::vformat(fmt_str, fmt_args)};
  fputs(out_str.c_str(), stderr);
}

/**
 * @brief print error message to `stderr` with a newline
 *
 * @tparam Args
 * @param fmt_str
 * @param args
 */
template <string_convertible... Args>
void eprintln(const std::string_view fmt_str, Args &&...args) {
  auto fmt_args{std::make_format_args(std::forward<Args>(args)...)};
  std::string out_str{std::vformat(fmt_str, fmt_args)};
  fputs(out_str.c_str(), stderr);
  fputs("\n", stderr);
}

#else

/**
 * @brief print error message to `std::cerr`
 *
 * @tparam Args
 * @param fmt
 * @param args
 */
template <could_to_string... Args>
void eprint(const std::string_view fmt, Args &&...args) {
  std::cerr << format(fmt, std::forward<Args>(args)...);
}

/**
 * @brief print error message to `std::cerr` with a newline
 *
 * @tparam Args
 * @param fmt
 * @param args
 */
template <could_to_string... Args>
void eprintln(const std::string_view fmt, Args &&...args) {
  std::cerr << format(fmt, std::forward<Args>(args)...) << "\n";
}

#endif

} // namespace Eden