#include "countif_parallel.h"

#include <cstdint>
#include <functional>
#include <iterator>
#include <vector>

template uint64_t CountIf<std::vector<int>::iterator, bool (*)(int64_t)>(
    std::vector<int>::iterator, std::vector<int>::iterator, bool (*)(int64_t));
