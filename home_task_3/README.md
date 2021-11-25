clang-format -i ../set_lib/set.h && 
clang-format -i ../main.cc

lcov -t "tests/test_set" -o coverage.info -c -d tests/  &&
genhtml -o report coverage.info

