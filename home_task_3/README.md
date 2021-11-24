clang-format -i ../matrix_calculator_lib/matrix_calculator.h && 
clang-format -i ../tests/test_matrix_calculator.cc &&
clang-format -i ../main.cc

lcov -t "tests/test_matrix_calculator" -o coverage.info -c -d tests/  &&
genhtml -o report coverage.info

./linters/run.sh


valgrind --tool=memcheck --leak-check=yes ./tests/test_matrix_calculator

