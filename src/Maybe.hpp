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
 *              0. `func` := `functor()`, `value` := `value_t()`
 *              1. form of `func(value)`
 *              2. return type of `func(value)` is not `void`
 * @tparam functor
 * @tparam value_t
 */
template <typename functor, typename... value_t>
concept functor_of = requires(functor func) {
  { func(value_t()...) };
  { !std::is_same_v<decltype(func(value_t()...)), void> };
};

template <typename T>
class Maybe {
  std::optional<T> value{};
  Maybe() = default;

 public:
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

  static Maybe<T> null() { return Maybe<T>(); }

  T extract() {
    if (value == std::nullopt) {
      throw std::runtime_error("Cannot extract the value.");
    }
    return std::move(value).value();
  }

  std::optional<T> get_raw() { return value; }

  auto exec(functor_of<T> auto &&func)
      -> decltype(Maybe<decltype(func(T()))>(func(T()))) {
    using type = decltype(func(T()));
    if (value == std::nullopt) {
      return Maybe<type>::null();
    }
    return Maybe<type>(func(std::move(value).value()));
  }
  auto exec(const functor_of<T> auto &&func)
      -> decltype(Maybe<decltype(func(T()))>(func(T()))) {
    using type = decltype(func(T()));
    if (value == std::nullopt) {
      return Maybe<type>::null();
    }
    return Maybe<type>(func(std::move(value).value()));
  }

  friend auto operator|(Maybe<T> &&maybe, functor_of<T> auto &&func)
      -> decltype(Maybe<decltype(func(T()))>(func(T()))) {
    using type = decltype(func(T()));
    auto &&value = std::move(maybe).get_raw();
    if (value == std::nullopt) {
      return Maybe<type>::null();
    }
    return Maybe<type>(func(value.value()));
  }
  friend auto operator|(Maybe<T> &maybe, functor_of<T> auto &&func)
      -> decltype(Maybe<decltype(func(T()))>(func(T()))) {
    using type = decltype(func(T()));
    auto &&value = std::move(maybe).get_raw();
    if (value == std::nullopt) {
      return Maybe<type>::null();
    }
    return Maybe<type>(func(value.value()));
  }
  friend auto operator|(Maybe<T> &&maybe, const functor_of<T> auto &&func)
      -> decltype(Maybe<decltype(func(T()))>(func(T()))) {
    using type = decltype(func(T()));
    auto &&value = std::move(maybe).get_raw();
    if (value == std::nullopt) {
      return Maybe<type>::null();
    }
    return Maybe<type>(func(value.value()));
  }
  friend auto operator|(Maybe<T> &maybe, const functor_of<T> auto &&func)
      -> decltype(Maybe<decltype(func(T()))>(func(T()))) {
    using type = decltype(func(T()));
    auto &&value = std::move(maybe).get_raw();
    if (value == std::nullopt) {
      return Maybe<type>::null();
    }
    return Maybe<type>(func(value.value()));
  }
};

template <typename T>
auto exec_maybe(Maybe<T> &&maybe, functor_of<T> auto &&func)
    -> decltype(Maybe<decltype(func(T()))>(func(T()))) {
  using type = decltype(func(T()));
  auto &&value = std::move(maybe).get_raw();
  if (value == std::nullopt) {
    return Maybe<type>::null();
  }
  return Maybe<type>(func(value.value()));
}
template <typename T>
auto exec_maybe(Maybe<T> &maybe, functor_of<T> auto &&func)
    -> decltype(Maybe<decltype(func(T()))>(func(T()))) {
  using type = decltype(func(T()));
  auto &&value = std::move(maybe).get_raw();
  if (value == std::nullopt) {
    return Maybe<type>::null();
  }
  return Maybe<type>(func(value.value()));
}
template <typename T>
auto exec_maybe(Maybe<T> &&maybe, const functor_of<T> auto &&func)
    -> decltype(Maybe<decltype(func(T()))>(func(T()))) {
  using type = decltype(func(T()));
  auto &&value = std::move(maybe).get_raw();
  if (value == std::nullopt) {
    return Maybe<type>::null();
  }
  return Maybe<type>(func(value.value()));
}
template <typename T>
auto exec_maybe(Maybe<T> &maybe, const functor_of<T> auto &&func)
    -> decltype(Maybe<decltype(func(T()))>(func(T()))) {
  using type = decltype(func(T()));
  auto &&value = std::move(maybe).get_raw();
  if (value == std::nullopt) {
    return Maybe<type>::null();
  }
  return Maybe<type>(func(value.value()));
}

template <typename T>
T extract_maybe(Maybe<T> &&maybe) {
  auto &&value = std::move(maybe).get_raw();
  if (value == std::nullopt) {
    throw std::runtime_error("Cannot extract the value.");
  }
  return value.value();
}
template <typename T>
T extract_maybe(Maybe<T> &maybe) {
  auto &&value = std::move(maybe).get_raw();
  if (value == std::nullopt) {
    throw std::runtime_error("Cannot extract the value.");
  }
  return value.value();
}

}  // namespace Eden