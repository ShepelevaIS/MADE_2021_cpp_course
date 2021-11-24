#include "set_lib/set.h"
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  Set<int64_t> set;
  std::vector<int64_t> elements{5, 4, 3, 2, 1};
  Set<int64_t> set_second(elements.begin(), elements.end());
  set_second.Print();
  set_second.PrintReversed();
  {
    int64_t to_find = 3;
    auto iter = set_second.Find(to_find);
    if (iter != set_second.End()) {
      std::cout << "Found " << to_find << std::endl;
    } else {
      std::cout << "Not found " << to_find << std::endl;
    }
  }

  {
    int64_t to_find = 6;
    auto iter = set_second.Find(to_find);
    if (iter != set_second.End()) {
      std::cout << "Found " << to_find << std::endl;
    } else {
      std::cout << "Not found " << to_find << std::endl;
    }
  }

  Set<int64_t> set_third{5, 4, 3, 2, 1};

  std::string operation;
  int64_t value;
  while (std::cin >> operation >> value) {
    if (operation == "insert") {
      set.Insert(value);
    } else if (operation == "exists") {
      if (set.Exists(value)) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
    } else if (operation == "delete") {
      set.Delete(value);
    } else if (operation == "next") {
      auto result = set.Next(value);
      if (result) {
        std::cout << result.value() << '\n';
      } else {
        std::cout << "none\n";
      }
    } else if (operation == "prev") {
      auto result = set.Prev(value);
      if (result) {
        std::cout << result.value() << '\n';
      } else {
        std::cout << "none\n";
      }
    }
  }
  return 0;
}