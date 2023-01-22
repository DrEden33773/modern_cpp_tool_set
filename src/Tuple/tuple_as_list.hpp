/**
 * @file tuple_as_list.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief a tool set to enable handling tuple as a `general list`
 * @version 0.1
 * @date 2022-10-30
 *
 * @copyright Copyright (c) 2022
 *
 */

/**
 * @note
        @b std::make_index_sequence<0>()
        @e will_generate_an_empty_sequence

        @b std::make_tuple(std::get<Index>(tuple)...)
            @b Index @p is_in @e index_sequence
        @e will_generate_empty_tuple @p iff @e index_sequence_empty
 */

#pragma once

#include "tuple_utility.hpp"

#include <functional>
#include <iostream>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <tuple>
#include <utility>

namespace Eden {

/// @brief @b get_the_head
/// @e (11,2,3,4)__head=11
/// @e ()__head->error
template <typename Type, typename... Types>
constexpr auto head(const std::tuple<Type, Types...> &tuple) {
  return std::get<0>(tuple);
}
void head(const std::tuple<> &tuple) {
  const char *error_info = "Tuple is empty! Can't get its head elem!";
  throw std::logic_error(error_info);
}

/// @brief @b get_the_tail
/// @e (11,2,3,4)__tail=(2,3,4)
/// @e (11)__tail=()
/// @e ()__tail->error
template <size_t... Index, typename... Types>
constexpr auto get_tail(std::index_sequence<Index...>,
                        const std::tuple<Types...> &tuple) {
  // template fold
  // for_each Index, add 1
  // this could get the correct index
  return std::make_tuple(std::get<Index + 1u>(tuple)...);
}
template <typename Type, typename... Types>
constexpr auto tail(const std::tuple<Type, Types...> &tuple) {
  return get_tail(std::make_index_sequence<sizeof...(Types)>(), tuple);
}
void tail(const std::tuple<> &tuple) {
  const char *error_info = "Tuple is empty! Can't get its tail tuple!";
  throw std::logic_error(error_info);
}

/// @brief @b get_the_last
/// @e (11,2,3,4)__last=(4)
/// @e ()__last->error
template <typename Type, typename... Types>
constexpr auto last(const std::tuple<Type, Types...> &tuple) {
  return std::get<sizeof...(Types)>(tuple);
}
void last(const std::tuple<> &tuple) {
  const char *error_info = "Tuple is empty! Can't get its last elem!";
  throw std::logic_error(error_info);
}

/// @brief @b remove_last
/// @e (11,2,3,4)__init=(11,2,3)
/// @e (11)__init=()
/// @e ()__init->error
template <size_t... Index, typename... Types>
constexpr auto remove_last(std::index_sequence<Index...>,
                           const std::tuple<Types...> &tuple) {
  return std::make_tuple(std::get<Index>(tuple)...);
}
template <typename Type, typename... Types>
constexpr auto init(const std::tuple<Type, Types...> &tuple) {
  return remove_last(std::make_index_sequence<sizeof...(Types)>(), tuple);
}
void init(const std::tuple<> &tuple) {
  const char *error_info = "Tuple is empty! Can't remove its last elem!";
  throw std::logic_error(error_info);
}

} // namespace Eden