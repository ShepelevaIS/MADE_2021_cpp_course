#ifndef HOME_TASK_4_COUNTIF_LIB_COUNTIF_H_
#define HOME_TASK_4_COUNTIF_LIB_COUNTIF_H_

#include <cstdint>

template <typename Iter, typename Pred>
uint64_t CountIf(Iter begin, Iter end, Pred pred);

#endif  // HOME_TASK_4_COUNTIF_LIB_COUNTIF_H_
