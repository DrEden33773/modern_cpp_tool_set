/**
 * @file IO.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief concepts about `IO`
 * @version 0.1
 * @date 2023-01-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <ostream>

namespace Eden {

template <typename T>
concept printable = requires(T &&t, std::ostream &os) {
  { os << std::forward<T>(t) };
};

} // namespace Eden