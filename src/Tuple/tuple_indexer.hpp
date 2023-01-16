/**
 * @file tuple_indexer.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief run-time indexer (different from `std::get<{constexpr}>(std::tuple)`)
 * @version 0.1
 * @date 2023-01-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "tuple_as_list.hpp"
#include <stdexcept>

namespace Eden {

/**
 * @brief continuously remove the first element of `tuple`
 *
 * @tparam Args
 * @param times
 * @param tuple
 * @return constexpr auto
 */
template <typename... Args>
constexpr auto multi_tail_opt(const std::tuple<Args...> &tuple,
                              std::size_t times) {
  return times > 0 ? multi_tail_opt(tail(tuple), times - 1) : tuple;
}

/**
 * @brief get the value of `args_tuple` on `idx`
 *
 * @tparam Args
 * @param idx
 * @param args_tuple
 * @return constexpr auto
 */
template <typename... Args>
constexpr auto get_tuple_value(std::size_t idx,
                               const std::tuple<Args...> &args_tuple) {
  if constexpr (sizeof...(Args) == 0) {
    throw std::logic_error("cannot index a empty tuple");
  }
  if (idx >= sizeof...(Args)) {
    throw std::out_of_range("index out of range");
  }
  // auto adjusted_tuple = multi_tail_opt(args_tuple, idx);
  return std::get<0>(args_tuple);
}

} // namespace Eden