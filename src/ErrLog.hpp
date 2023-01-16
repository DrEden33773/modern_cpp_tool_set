/**
 * @file ErrLog.hpp
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

namespace Eden {

/**
 * @brief print error message to `std::cerr`
 *
 * @tparam Args
 * @param fmt
 * @param args
 */
template <could_to_string... Args>
void err_log(std::string_view fmt, Args &&...args) {
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
void err_log_ln(std::string_view fmt, Args &&...args) {
  std::cerr << format(fmt, std::forward<Args>(args)...) << "\n";
}

} // namespace Eden