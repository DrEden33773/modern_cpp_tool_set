#pragma once

#include "../Concepts.hpp"

#include <any>
#include <functional>
#include <iostream>
#include <ostream>
#include <sstream>
#include <tuple>
#include <type_traits>
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
constexpr void print_tuple(const std::tuple<Args...> &tuple) {
  /**
   *  @brief take `tuple := (1, 2, 3, 4, 5)`
        alone with
      @code
        func := f <-> [](const auto &element, std::size_t current_index) {
          if (current_index != 0) {
            std::cout << ", ";
          }
          std::cout << element;
        }
      @code
      for example:
      @code
        called `for_each`:
          -> unwrap_tuple<f, tuple, 5>::get_forward()
            -> unwrap_tuple<f, tuple, 4>::get_forward()
              -> unwrap_tuple<f, tuple, 3>::get_forward()
                -> unwrap_tuple<f, tuple, 2>::get_forward()
                  -> unwrap_tuple<f, tuple, 1>::get_forward()
                  <- f(element = tuple[0], current_index = 0) => `1`
                <- f(element = tuple[1], current_index = 1) => `, 2`
              <- f(element = tuple[2], current_index = 2) => `, 3`
            <- f(element = tuple[3], current_index = 3) => `, 4`
          <- f(element = tuple[4], current_index = 4) => `, 5`
        end of `for_each`
      @code
      Finally, it appears like you've outputted `(1, 2, 3, 4, 5)`.
      But, it could be separated into `{1} $ {, 2} $ {, 3} $ {, 4} $ {, 5}`
   *
   */
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
constexpr void println_tuple(const std::tuple<Args...> &tuple) {
  print_tuple(tuple);
  std::cout << std::endl;
}

/**
 * @brief construct `std::pair<T, U>` with `std::tuple<T, U>`
 *
 * @tparam T
 * @tparam U
 * @param t
 * @return std::pair<T, U>
 */
template <typename T, typename U>
constexpr auto tuple_to_pair(const std::tuple<T, U> &t) -> std::pair<T, U> {
  return std::make_pair(std::get<0>(t), std::get<1>(t));
}

/**
 * @brief into dyn vec
 *
 * @tparam Args
 * @param tuple
 * @return constexpr auto
 */
template <typename... Args>
constexpr auto into_dyn_vec(const std::tuple<Args...> &tuple)
    -> std::vector<std::any> {
  auto vec =
      [&]<std::size_t... Idx, typename... Ts>(std::index_sequence<Idx...>) {
        return std::vector<std::any>{std::get<Idx>(tuple)...};
      }(std::make_index_sequence<sizeof...(Args)>());
  return vec;
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
constexpr std::ostream &operator<<(std::ostream &out,
                                   const std::tuple<Args...> &tuple) {
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
constexpr std::string to_string(const std::tuple<Args...> &tuple) {
  std::string res;
  res += "(";
  Eden::for_each(tuple, [&](const auto &element, size_t current_index) {
    if (current_index != 0) {
      res += ", ";
    }
    if constexpr (Eden::could_to_string<
                      typename std::common_type<Args...>::type>) {
      res += std::to_string(element);
    } else {
      res += [&]() {
        std::ostringstream oss;
        oss << element;
        return oss.str();
      }();
    }
  });
  res += ")";
  return res;
}

} // namespace std