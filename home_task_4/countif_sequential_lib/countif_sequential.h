#ifndef HOME_TASK_4_COUNTIF_SEQUENTIAL_LIB_COUNTIF_SEQUENTIAL_H_
#define HOME_TASK_4_COUNTIF_SEQUENTIAL_LIB_COUNTIF_SEQUENTIAL_H_

#include <cstdint>

template <typename Iter, typename Pred>
uint64_t CountIf(Iter begin, Iter end, Pred pred) {
  uint64_t result = 0;
  for (auto iter = begin; iter != end; ++iter) {
    result += pred(*iter);
  }
  return result;
}

#endif  // HOME_TASK_4_COUNTIF_SEQUENTIAL_LIB_COUNTIF_SEQUENTIAL_H_
