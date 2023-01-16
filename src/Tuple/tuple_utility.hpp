#pragma once

#include "../Concepts.hpp"

#include <functional>
#include <iostream>
#include <ostream>
#include <sstream>
#include <tuple>
#include <utility>

namespace Eden {

/// @brief @b unwrap_the_tuple
template <class Func, class Tuple, size_t N> // N >= 2
struct unwrap_tuple {
  constexpr static auto get_forward(const Tuple &tuple, Func f) {
    unwrap_tuple<Func, Tuple, N - 1>::get_forward(tuple, f);
    return f(std::get<N - 1>(tuple), N - 1);
  }
};
template <class Func, class Tuple> // N == 1
struct unwrap_tuple<Func, Tuple, 1> {
  constexpr static auto get_forward(const Tuple &tuple, Func f) {
    return f(std::get<0>(tuple), 0);
  }
};
template <class Func, class Tuple> // N == 0
struct unwrap_tuple<Func, Tuple, 0> {
  constexpr static auto get_forward(const Tuple &tuple, Func f) { return; }
};

/// @brief @b for_each_in_tuple
template <class Func, class... Args>
constexpr auto for_each(const std::tuple<Args...> &tuple, Func f) {
  using Tuple = decltype(tuple);
  return unwrap_tuple<Func, Tuple, sizeof...(Args)>::get_forward(tuple, f);
}

/// @brief @b print_tuple
template <printable... Args>
void print_tuple(const std::tuple<Args...> &tuple) {
  std::cout << "(";
  for_each(tuple, [](const auto &element, std::size_t current_index) {
    if (current_index != 0) {
      std::cout << ", ";
    }
    std::cout << element;
  });
  std::cout << ")";
}

/// @brief @b println_tuple
template <printable... Args>
void println_tuple(const std::tuple<Args...> &tuple) {
  print_tuple(tuple);
  std::cout << std::endl;
}

/**
 * @brief construct `std::pair<T, U>` with `std::tuple<T, U>`
 *
 * @tparam T
 * @tparam U
 * @param t
 * @return decltype(std::make_pair(std::get<0>(t), std::get<1>(t)))
 */
template <typename T, typename U>
auto tuple_to_pair(const std::tuple<T, U> &t)
    -> decltype(std::make_pair(std::get<0>(t), std::get<1>(t))) {
  return std::make_pair(std::get<0>(t), std::get<1>(t));
}

} // namespace Eden

/// @attention
///
/// You have to expand methods for each class in `std_namespace`.
///
/// Generally, if you haven't assign the namespace for a method,
/// the compiler will automatically search in the order below:
///   global_namespace => std_namespace => <implicit_namespace_equal_to_class>
/// .
///
/// However, in `concept` system, it will only search in the order below:
///   std_namespace => <implicit_namespace_equal_to_class>
/// .
///
/// Since it's impossible to directly expand a method out of a class in cpp
/// (just like what could be done in Kotlin),
/// expand the method in `std` is a necessary schedule.
namespace std {

/**
 * @brief expand `operator<<` for `std::tuple` (in `std_namespace`)
 *
 * @tparam Args
 * @param out
 * @param tuple
 * @return std::ostream&
 */
template <Eden::printable... Args>
std::ostream &operator<<(std::ostream &out, const std::tuple<Args...> &tuple) {
  out << "(";
  Eden::for_each(tuple, [&](const auto &element, size_t current_index) {
    if (current_index != 0) {
      out << ", ";
    }
    out << element;
  });
  out << ")";
  return out;
}

/**
 * @brief expand `to_string` for `std::tuple` (in `std_namespace`)
 *
 * @tparam Args
 * @param tuple
 * @return std::string
 */
template <Eden::string_convertible... Args>
std::string to_string(const std::tuple<Args...> &tuple) {
  // std::ostringstream oss;
  // oss << tuple;
  // return oss.str();

  std::string res;
  res += "(";
  Eden::for_each(tuple, [&](const auto &element, size_t current_index) {
    if (current_index != 0) {
      res += ", ";
    }
    res += std::to_string(element);
  });
  res += ")";
  return res;
}

} // namespace std