/**
 * @file fib_seq.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "../Format.hpp"
#include "../Print.hpp"
#include "../ThreadPool.hpp"
#include <functional>

namespace Test {

void fib_seq_test() {
  static constexpr std::size_t EOF_IDX = 10;
  Eden::ThreadPool fib_pool{};

  std::vector<std::future<std::size_t>> fib_seq_res{};
  fib_seq_res.reserve(EOF_IDX);

  for (std::size_t end_idx = 0; end_idx < EOF_IDX; ++end_idx) {
    fib_seq_res.emplace_back(fib_pool.enqueue([end_idx] {
      std::size_t a{1};
      std::size_t b{1};
      std::size_t c{2};
      if (end_idx < 2) [[unlikely]] {
        return a;
      }
      std::size_t idx{2};
      while (true) [[likely]] {
        c = a + b;
        if (idx == end_idx) [[unlikely]] {
          break;
        }
        a = b;
        b = c;
        ++idx;
      }
      return c;
    }));
  }

  Eden::println("Here are the result (from fib[0] to fib[{}]) => \n",
                EOF_IDX - 1);
  std::string res_str{};
  for (auto &&res : fib_seq_res) {
    res_str += Eden::format("{} ", res.get());
  }
  Eden::println("{}\n", res_str);
}

} // namespace Test