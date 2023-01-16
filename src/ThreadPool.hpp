/**
 * @file ThreadPool.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <cassert>
#include <future>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

namespace Eden {

class ThreadPool {
private:
  void init_threads(std::size_t numThreads) {
    for (std::size_t i = 0; i < numThreads; ++i) {
      threads.emplace_back([&]() {
        for (;;) {
          std::function<void()> task;
          // 1. Try to get a task from the queue.

          // In this field, the queue should be exclusive instead of shared.
          // So we need to lock the queue.
          /* begin of field */
          {
            // lock the queue
            std::unique_lock<std::mutex> lock(queueMutex);
            // wait when `the queue is empty` and `not stopped`
            condition.wait(lock, [&]() { return stop || !tasks.empty(); });
            if (stop && tasks.empty()) {
              return;
            }
            task = std::move(tasks.front());
            tasks.pop();
          }
          /* end of field */
          // We should end this field == We should release the lock.
          // That's because we hope to see the `task queue` is shared for IO at
          // most time.
          // Clearly, the lock after waiting is totally unnecessary.

          // 2. execute the task (fetched from the queue's front)
          task();
        }
      });
    }
  }

public:
  /// @brief Construct a new Thread Pool object (with a given number of threads)
  explicit ThreadPool(std::size_t numThreads) {
    if (numThreads > std::thread::hardware_concurrency()) {
      std::cout << "Warning: The number of threads is larger than the number "
                   "of hardware concurrency.\n\n";
      std::cout << "Now, automatically set it to the concurrency.\n\n";
      numThreads = std::thread::hardware_concurrency();
    }
    init_threads(numThreads);
  }

  /// @brief Construct a new Thread Pool object (with `hardware_concurrency()`)
  ThreadPool() { init_threads(std::thread::hardware_concurrency()); }

  template <typename T> auto enqueue(T task) -> std::future<decltype(task())> {
    // A future object is a handle to a value that is not yet available.
    // It is a way to access the result of an asynchronous operation.

    // 1. wrap the task into a packaged_task
    // (will automatically create a future object)
    auto wrapper = std::make_shared<std::packaged_task<decltype(task())()>>(
        std::move(task));
    // 2. push the task into the queue
    // (needs to change the queue from `shared` to `exclusive`)
    // (otherwise, the queue could be changed by multiple threads)
    {
      std::unique_lock<std::mutex> lock(queueMutex);
      if (stop) {
        throw std::runtime_error("enqueue on stopped ThreadPool");
      }
      tasks.emplace([=]() { (*wrapper)(); });
    }
    // 3. notify one thread to execute the task
    condition.notify_one();
    // 4. return the connect future object
    return wrapper->get_future();
  }

  ~ThreadPool() {
    // set status to stop
    {
      std::unique_lock<std::mutex> lock(queueMutex);
      stop = true;
    }
    condition.notify_all(); // notify all threads to stop
    // wait for all threads to stop
    for (auto &thread : threads) {
      thread.join();
    }
  }

  // copy constructor and copy assignment operator are deleted
  ThreadPool(const ThreadPool &copied) = delete;
  ThreadPool &operator=(const ThreadPool &copied) = delete;

  // move constructor and move assignment operator are deleted
  ThreadPool(ThreadPool &&moved) = delete;
  ThreadPool &operator=(ThreadPool &&moved) = delete;

private:
  /// @brief a thread pool
  std::vector<std::thread> threads;

  /// @brief a task queue
  std::queue<std::function<void()>> tasks;

  /// @brief a mutex to protect the task queue
  std::mutex queueMutex;

  /// @brief a condition variable to notify threads
  std::condition_variable condition;

  /// @brief a flag to indicate whether the thread pool is stopped
  bool stop = false;
};

} // namespace Eden