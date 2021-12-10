#include <iostream>
#include <random>
#include <string>
#include <vector>

std::vector<int> RandomIntegers(size_t size, int min_value, int max_value, std::mt19937* mt_ptr) {
  auto& mt = *mt_ptr;
  std::vector<int> result;
  result.reserve(size);
  for (size_t i = 0; i < size; ++i) {
    result.push_back(std::uniform_int_distribution<int>(min_value, max_value)(mt));
  }
  return result;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Wrong number of arguments" << std::endl;
    return 0;
  }
  static constexpr int MIN_VALUE = -50;
  static constexpr int MAX_VALUE = 50;
  std::ios_base::sync_with_stdio(false);
  size_t size = std::stoi(argv[1]);
  size_t seed = std::stoi(argv[2]);
  std::mt19937 mt(seed);
  std::vector<int> values = RandomIntegers(size, MIN_VALUE, MAX_VALUE, &mt);
  for (auto value: values) {
    std::cout << value << " ";
  }
  return 0;
}
