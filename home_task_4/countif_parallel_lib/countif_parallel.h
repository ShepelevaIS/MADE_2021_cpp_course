#ifndef HOME_TASK_4_COUNTIF_PARALLEL_LIB_COUNTIF_PARALLEL_H_
#define HOME_TASK_4_COUNTIF_PARALLEL_LIB_COUNTIF_PARALLEL_H_

#include <atomic>
#include <cstdint>
#include <iterator>
#include <thread>  // NOLINT
#include <vector>

template <typename Iter, typename Pred, typename Ret>
void CountBatch(Iter begin, Iter end, Pred pred, Ret ret) {
  uint64_t result = 0;
  for (auto iter = begin; iter != end; ++iter) {
    result += pred(*iter);
  }
  ret(result);
}

template <typename Iter, typename Pred>
uint64_t CountIf(Iter begin, Iter end, Pred pred) {
  uint64_t result = 0;
  const size_t num_threads = 4;
  size_t size = std::distance(begin, end);
  size_t num_per_thread = size / num_threads;
  std::atomic<uint64_t> total_count = 0;
  auto ret = [&total_count](uint64_t count) { total_count += count; };
  std::vector<std::thread> threads;
  threads.reserve(num_threads);
  auto iter = begin;
  for (size_t i = 0; i + 1 < num_threads; ++i) {
    threads.emplace_back(
        CountBatch<decltype(iter), decltype(pred), decltype(ret)>, iter,
        iter + num_per_thread, pred, ret);
    std::advance(iter, num_per_thread);
  }
  threads.emplace_back(
      CountBatch<decltype(iter), decltype(pred), decltype(ret)>, iter, end,
      pred, ret);
  for (size_t i = 0; i < num_threads; ++i) {
    threads[i].join();
  }
  return total_count;
}

#endif  // HOME_TASK_4_COUNTIF_PARALLEL_LIB_COUNTIF_PARALLEL_H_
