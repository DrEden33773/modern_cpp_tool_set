/**
 * @file Maybe.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <concepts>
#include <functional>
#include <optional>
#include <stdexcept>
#include <type_traits>

namespace Eden {

/**
 * @brief
 *       Concept `functor_of` requires an type param `value_t`.
 *       It needs to satisfy =>
 *              0. func := functor(), value := value_t()
 *              1. form of `func(value)`
 *              2. return type of `func(value)` is not `void`
 * @tparam functor
 * @tparam value_t
 */
template <typename functor, typename value_t>
concept functor_of = requires(functor func, value_t value) {
  { func(value) };
  { !std::is_same_v<decltype(func(value)), void> };
};

template <typename T>
class Maybe {
  std::optional<T> value{};

 public:
  Maybe() = default;

  explicit Maybe(T &init) : value{init} {}
  explicit Maybe(const T &init) : value{init} {}
  explicit Maybe(const T &&init) : value{init} {}
  explicit Maybe(T &&init) : value{init} {}

  static Maybe<T> from_optional(std::optional<T> &optional) {
    Maybe<T> ret;
    ret.value = optional;
    return ret;
  }
  static Maybe<T> from_optional(const std::optional<T> &optional) {
    Maybe<T> ret;
    ret.value = optional;
    return ret;
  }

  T extract() {
    if (value == std::nullopt) {
      throw std::runtime_error("Cannot extract the value.");
    }
    return value.value();
  }

  std::optional<T> get_optional() { return value; }

  auto exec(functor_of<T> auto func)
      -> decltype(Maybe<decltype(func(T()))>(func(T()))) {
    using type = decltype(func(T()));
    if (value == std::nullopt) {
      return Maybe<type>::from_optional(std::optional<type>{std::nullopt});
    }
    return Maybe<type>(func(value.value()));
  }
};

}  // namespace Eden