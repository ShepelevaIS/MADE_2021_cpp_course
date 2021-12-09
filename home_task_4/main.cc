#include <countif.h>

#include <chrono>  // NOLINT
#include <iostream>
#include <random>
#include <vector>

std::vector<int> RandomIntegers(size_t size, std::mt19937& mt) {  // NOLINT
  std::vector<int> result;
  result.reserve(size);
  for (size_t i = 0; i < size; ++i) {
    result.push_back(std::uniform_int_distribution<int>(-50, 50)(mt));
  }
  return result;
}

bool Predicate(int64_t value) { return value < 10; }

int main() {
  const size_t SIZE = 100000000;
  const size_t SEED = 1337;
  std::mt19937 mt(SEED);
  std::vector<int> values = RandomIntegers(SIZE, mt);
  std::cout << "Done Generating" << std::endl;
  auto start = std::chrono::steady_clock::now();
  std::cout << CountIf(values.begin(), values.end(), Predicate) << '\n';
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
  return 0;
}
