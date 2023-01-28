/**
 * @file pair_utility.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <functional>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

#include "../Concepts.hpp"

namespace std {

/**
 * @brief expand `operator<<` for `std::pair` (in `std_namespace`)
 *
 * @tparam T
 * @tparam P
 * @param os
 * @param p
 * @return std::ostream&
 */
template <Eden::printable T, Eden::printable U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}

/**
 * @brief expand `to_string` for `std::pair` (in `std_namespace`)
 *
 * @tparam Args
 * @param tuple
 * @return std::string
 */
template <Eden::string_convertible T, Eden::string_convertible U>
std::string to_string(const std::pair<T, U> &pair) {
  std::string res;
  res += '(';
  if constexpr (Eden::could_to_string<T>) {
    res += std::to_string(pair.first);
  } else {
    res += [&] {
      std::ostringstream oss;
      oss << pair.first;
      return oss.str();
    }();
  }
  res += ", ";
  if constexpr (Eden::could_to_string<U>) {
    res += std::to_string(pair.second);
  } else {
    res += [&] {
      std::ostringstream oss;
      oss << pair.second;
      return oss.str();
    }();
  }
  res += ')';
  return res;
}

}  // namespace std

#if _GLIBCXX_RELEASE >= 13

#include <format>

namespace std {}  // namespace std

#endif

namespace Eden {

/**
 * @brief construct `std::tuple<T, U>` with `std::pair<T, U>`
 *
 * @tparam T
 * @tparam U
 * @param p
 * @return decltype(std::make_tuple(p.first, p.second))
 */
template <typename T, typename U>
auto pair_to_tuple(const std::pair<T, U> &p) -> std::tuple<T, U> {
  return std::make_tuple(p.first, p.second);
}

}  // namespace Eden