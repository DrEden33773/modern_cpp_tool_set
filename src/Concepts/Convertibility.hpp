/**
 * @file Convertibility.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <concepts>
#include <sstream>
#include <string>

namespace Eden {

template <typename T>
concept oss_obj_bin_operative = requires(T &&t, std::ostringstream &oss) {
  { oss << std::forward<T>(t) };
};

template <typename T>
concept could_to_string = requires(T &&t) {
  { std::to_string(std::forward<T>(t)) } -> std::convertible_to<std::string>;
};

template <typename T>
concept string_convertible = oss_obj_bin_operative<T> or could_to_string<T>;

} // namespace Eden