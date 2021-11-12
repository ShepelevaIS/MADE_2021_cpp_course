#include "matrix_calculator_lib/matrix_calculator.h"
#include <iostream>

template <typename Data> void printVector(const Vector<Data> &vector) {
  for (size_t i = 0; i < vector.Size(); ++i) {
    std::cout << vector[i] << " ";
  }
  std::cout << std::endl;
}

template <typename Data> void printMatrix(const Matrix<Data> &matrix) {
  for (size_t i = 0; i < matrix.RowSize(); ++i) {
    printVector(matrix[i]);
  }
}

int main() {
  Matrix<int> matrix({{0, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<double> matrix_expected(
      {{-1, 2, -1}, {2, -7, 4}, {-1, 4.66667, -2.66667}});
  auto res = matrix.Inverse();
  printMatrix(matrix_expected - res);
  return 0;
}