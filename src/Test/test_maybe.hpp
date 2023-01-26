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
#include <initializer_list>
#include <string>
#include <utility>
#include <vector>

#include "../Maybe.hpp"
#include "../Print.hpp"

namespace Test {

void test_maybe() {
  using Eden::Maybe;
  using Eden::print;
  using Eden::println;
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

  static constexpr initializer_list<int> initializer = {15, 6,  1, 0,
                                                        32, 17, 24};

  auto final_vec = Maybe<vector<int>>(initializer)
                       .exec(sort)
                       .exec(for_each_add_one)
                       .exec(reverse)
                       .extract();

  auto final_sum = Maybe<vector<int>>(final_vec).exec(accumulate).extract();

  print("final_vec: ");
  for (auto num : final_vec) {
    print("{} ", num);
  }
  println();
  println("sum of final_vec: {}", final_sum);
  println();
}

}  // namespace Test