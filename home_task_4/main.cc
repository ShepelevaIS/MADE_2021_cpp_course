#include <countif.h>

#include <chrono>  // NOLINT
#include <iostream>
#include <vector>

template <typename Data, typename Stream>
std::vector<Data> ReadVector(Stream& stream) {  // NOLINT
  std::vector<Data> result;
  Data value;
  while (std::cin >> value) {
    result.push_back(value);
  }
  return result;
}

bool Predicate(int64_t value) { return value < 10; }

int main() {
  std::ios_base::sync_with_stdio(false);
  auto values = ReadVector<int>(std::cin);
  auto start = std::chrono::steady_clock::now();
  std::cout << CountIf(values.begin(), values.end(), Predicate) << '\n';
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cerr << "elapsed time: " << elapsed_seconds.count() << "s\n";
  return 0;
}
