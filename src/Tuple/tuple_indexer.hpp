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

#include <any>
#include <stdexcept>
#include <utility>
#include <vector>

#include "tuple_as_list.hpp"
#include "tuple_utility.hpp"

namespace Eden {

/**
 * @brief continuously remove the first element of `tuple`
 * @attention Impossible to implement!
 * @tparam Args
 * @param times
 * @param tuple
 * @return constexpr auto
 */
// template <typename... Args>
// constexpr auto multi_tail_opt(const std::tuple<Args...> &tuple,
//                               std::size_t times) {
//   return times > 0 ? multi_tail_opt(tail(tuple), times - 1) : tuple;
// }

/**
 * @brief Get the value of `args_tuple` on `idx` (same as std::get)
 *        So it cannot get the value during `run time`
 * @tparam Args
 * @param idx
 * @param args_tuple
 * @return constexpr auto
 */
template <typename... Args, std::size_t idx>
constexpr auto get_tuple_value(const std::tuple<Args...> &args_tuple) {
  static_assert(sizeof...(Args) != 0, "cannot index a empty tuple");
  static_assert(idx < sizeof...(Args), "index out of range");
  return std::get<idx>(args_tuple);
}

}  // namespace Eden