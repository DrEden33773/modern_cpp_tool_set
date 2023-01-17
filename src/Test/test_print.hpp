/**
 * @file test_print.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "../AdvancedPair.hpp"
#include "../AdvancedTuple.hpp"
#include "../Print.hpp"

#include <iostream>
#include <tuple>
#include <utility>

namespace Test {

// print("{}", 1);
//   => 1
// print("{}, {}", 1, 2);
//   => 1, 2
// print("{1}, {0}", 1, 2);
//   => 2, 1
// print("{1}, {0}, {}", 1, 2);
//   => 2, 1, 1
// print("{0}, {}, {1}, {}", 1, 2);
//   => 1, 1, 2, 2
// print("{{0}} = {0}, {{1}} = {1}", 1, 2)
//   => {0} = 1, {1} = 2

struct Point {
  double x{};
  double y{};
  friend std::ostream &operator<<(std::ostream &os, const Point &p) {
    return os << '(' << p.x << ", " << p.y << ')';
  }
};

void test_print() {
  using Eden::print;
  using Eden::println;

  println("{}", 1);
  println("{}, {}", 1, 2);
  println("{1}, {0}", 1, 2);
  println("{1}, {0}, {}", 1, 2);
  println("{0}, {}, {1}, {}", 1, 2);
  println("{}", Point{1, 2});
  println("{}", std::make_tuple(1, 2, 3));
  println("{}", std::make_pair(1, 2));
  println("{}", std::make_pair(Point{1, 2}, Point{3, 4}));
  println();

  println("Whether `std::tuple<int, double>` is `printable` => {}",
          Eden::printable<std::tuple<int, double>>);

  println("Whether `std::tuple<int, std::tuple<double, int, float>>` is "
          "`printable` => {}",
          Eden::printable<std::tuple<int, std::tuple<double, int, float>>>);

  println("Whether `Struct Point` is `printable` => {}",
          Eden::printable<Point>);

  println("Whether `std::tuple<std::tuple<double, int, float>, Point>` is "
          "`printable` => {}",
          Eden::printable<std::tuple<std::tuple<double, int, float>, Point>>);
  println();

  println("{{0}} = {0}, {{1}} = {1}", 1, 2);
  println(R"("{{0}}" = {}, "{{1}}" = {})", 1, 2);
  println();

  println("`test_Print()` passed!");
  println();
}

} // namespace Test