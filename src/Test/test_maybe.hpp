/**
 * @file test_maybe.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <string>
#include <utility>
#include <vector>

#include "../Maybe.hpp"
#include "../Print.hpp"

namespace Test {

int _accumulate(std::vector<int> vec) {
  int sum = 0;
  std::for_each(vec.begin(), vec.end(),
                [&sum](int num) mutable { sum += num; });
  return sum;
}

void test_maybe() {
  using Eden::Maybe;
  using std::initializer_list;
  using std::vector;

  auto sort = [](vector<int> vec) {
    std::sort(vec.begin(), vec.end());
    return vec;
  };
  auto for_each_add_one = [](vector<int> vec) {
    std::for_each(vec.begin(), vec.end(), [](int num) { return num + 1; });
    return vec;
  };
  auto reverse = [](vector<int> vec) {
    std::reverse(vec.begin(), vec.end());
    return vec;
  };
  auto accumulate = [](vector<int> vec) {
    int sum = 0;
    std::for_each(vec.begin(), vec.end(),
                  [&sum](int num) mutable { sum += num; });
    return sum;
  };

  static const vector<int> vec{15, 6, 1, 0, 32, 17, 24};

  auto final_vec = Maybe(vec)
                       .exec(sort)
                       .exec(for_each_add_one)
                       .exec(reverse)
                       .exec(for_each_add_one)
                       .extract();
  auto same_final_vec = Maybe(vec) | sort | for_each_add_one | reverse |
                        for_each_add_one | Eden::extract;

  auto sum = Maybe(final_vec).exec(accumulate).extract();
  auto same_sum = Maybe(final_vec) | accumulate | Eden::extract;

  auto temp_maybe = Maybe(final_vec);
  auto a_copied_sum = temp_maybe | _accumulate | Eden::extract;
  auto b_copied_sum = temp_maybe | _accumulate | Eden::extract;

  assert(final_vec == same_final_vec);
  assert(sum == same_sum);
  assert(a_copied_sum == b_copied_sum);

#ifdef __eden_lib_print
  using Eden::print;
  using Eden::println;
  print("final_vec: ");
  for (auto num : final_vec) {
    print("{} ", num);
  }
  println();
  println("sum of final_vec: {}", a_copied_sum);
  println();
#else
  std::cout << "final_vec: ";
  for (auto num : final_vec) {
    std::cout << num << " ";
  }
  std::cout << "\n";
  std::cout << "sum of final_vec: " << str_sum;
  std::cout << "\n";
#endif
}

}  // namespace Test