#include "matrix_calculator.h"
#include <gtest/gtest.h>
#include <vector>

TEST(VectorTest, VectorCreateWith) {
  Vector<int64_t> vector({1, 2, 4}, 3);
  EXPECT_EQ(4, vector[2]);
}

TEST(VectorTest, VectorCreateFromVector) {
  std::vector<int64_t> std_vector{1, 3, 4};
  Vector<int64_t> vector(std_vector.data(), std_vector.size());
  EXPECT_EQ(4, vector[2]);
}

TEST(VectorTest, VectorCreate) {
  int64_t arr[] = {1, 2, 3, 4, 5};
  Vector<int64_t> vector(arr, 5, false);
  EXPECT_EQ(5, vector[4]);
}

TEST(VectorTest, MatrixCreate) {
  Matrix<int64_t> matrix(5, 6);
  matrix[0][0] = 1337;
  EXPECT_EQ(1337, matrix[0][0]);
}

TEST(VectorTest, SumVectors) {
  Vector<int64_t> vector_first({1, 2, 4}, 3);
  Vector<int64_t> vector_second({5, 6, 7});
  Vector<int64_t> vector_expected({6, 8, 11});
  auto vector = vector_first + vector_second;
  EXPECT_EQ(vector_expected, vector);
}

TEST(VectorTest, SubstractVectors) {
  Vector<int64_t> vector_first({1, 2, 4}, 3);
  Vector<int64_t> vector_second({5, 6, 7});
  Vector<int64_t> vector_expected({-4, -4, -3});
  auto vector = vector_first - vector_second;
  EXPECT_EQ(vector_expected, vector);
}

TEST(VectorTest, VectorElementwiseProduct) {
  Vector<int64_t> vector_first({1, 2, 4}, 3);
  Vector<int64_t> vector_second({5, 6, 7});
  Vector<int64_t> vector_expected({5, 12, 28});
  auto vector = vector_first * vector_second;
  EXPECT_EQ(vector_expected, vector);
}

TEST(VectorTest, VectorAdditionAssignment) {
  Vector<int64_t> vector_first({1, 2, 4}, 3);
  Vector<int64_t> vector_second({5, 6, 7});
  Vector<int64_t> vector_expected({6, 8, 11});
  vector_first += vector_second;
  EXPECT_EQ(vector_expected, vector_first);
}

TEST(VectorTest, VectorSubtractionAssignment) {
  Vector<int64_t> vector_first({1, 2, 4}, 3);
  Vector<int64_t> vector_second({5, 6, 7});
  Vector<int64_t> vector_expected({-4, -4, -3});
  vector_first -= vector_second;
  EXPECT_EQ(vector_expected, vector_first);
}

TEST(VectorTest, VectorMultiplyAssignment) {
  Vector<int64_t> vector_first({1, 2, 4}, 3);
  Vector<int64_t> vector_second({5, 6, 7});
  Vector<int64_t> vector_expected({5, 12, 28});
  vector_first *= vector_second;
  EXPECT_EQ(vector_expected, vector_first);
}

TEST(VectorTest, VectorSumNumber) {
  Vector<int64_t> vector_first({1, 2, 4}, 3);
  Vector<int64_t> vector_expected({5, 6, 8});
  auto vector = vector_first + 4;
  EXPECT_EQ(vector_expected, vector);
}

TEST(VectorTest, VectorSubstractNumber) {
  Vector<int64_t> vector_first({1, 2, 4}, 3);
  Vector<int64_t> vector_expected({-4, -3, -1});
  auto vector = vector_first - 5;
  EXPECT_EQ(vector_expected, vector);
}

TEST(VectorTest, VectorMultiplyNumber) {
  Vector<int64_t> vector_first({1, 2, 4}, 3);
  Vector<int64_t> vector_expected({3, 6, 12});
  auto vector = vector_first * 3;
  EXPECT_EQ(vector_expected, vector);
}

TEST(MatrixTest, GeColumn) {
  Matrix<int64_t> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<int64_t> vector_expected({3, 6, 9}, false);
  auto res = matrix.GetColumn(2);
  EXPECT_EQ(vector_expected, res);
}

TEST(MatrixTest, MatrixPlusMatrix) {
  Matrix<int64_t> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<int64_t> matrix_second({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<int64_t> matrix_expected({{2, 4, 6}, {8, 10, 12}, {14, 16, 18}});
  auto res = matrix_first + matrix_second;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixPlusNumber) {
  Matrix<int64_t> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  int64_t number = 1;
  Matrix<int64_t> matrix_expected({{2, 3, 4}, {5, 6, 7}, {8, 9, 10}});
  auto res = matrix_first + number;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMinusMatrix) {
  Matrix<int64_t> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<int64_t> matrix_second({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<int64_t> matrix_expected({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
  auto res = matrix_first - matrix_second;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMinusNumber) {
  Matrix<int64_t> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  int64_t number = -1;
  Matrix<int64_t> matrix_expected({{2, 3, 4}, {5, 6, 7}, {8, 9, 10}});
  auto res = matrix_first - number;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMultiplyMatrix) {
  Matrix<int64_t> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<int64_t> matrix_second({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<int64_t> matrix_expected({{1, 4, 9}, {16, 25, 36}, {49, 64, 81}});
  auto res = matrix_first * matrix_second;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMultiplyNumber) {
  Matrix<int64_t> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  int64_t number = 2;
  Matrix<int64_t> matrix_expected({{2, 4, 6}, {8, 10, 12}, {14, 16, 18}});
  auto res = matrix_first * number;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, GetMainDiagonal) {
  Matrix<int64_t> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<int64_t> vector_expected({1, 5, 9});
  auto res = matrix.GetDiagonal();
  EXPECT_EQ(vector_expected, res);
}

TEST(MatrixTest, GetMinorDiagonal) {
  Matrix<int64_t> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<int64_t> vector_expected({3, 5, 7});
  auto res = matrix.GetDiagonal(false);
  EXPECT_EQ(vector_expected, res);
}

TEST(MatrixTest, TransposeMatrix) {
  Matrix<int64_t> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 3, 4}});
  Matrix<int64_t> matrix_expected({{1, 4, 7, 1}, {2, 5, 8, 3}, {3, 6, 9, 4}});
  auto res = matrix.Transpose();
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMatrixProduct) {
  Matrix<int64_t> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 3, 4}});
  Matrix<int64_t> matrix_second({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<int64_t> matrix_expected(
      {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}, {41, 49, 57}});
  auto res = matrix_first.Product(matrix_second);
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixVectorProduct) {
  Vector<int64_t> vector({5, 6, 7}, false);
  Matrix<int64_t> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 3, 4}});
  Matrix<int64_t> matrix_expected = {{38}, {92}, {146}, {51}};
  auto res = matrix.Product(vector);
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, VectorMatrixProduct) {
  Vector<int64_t> vector({5, 6, 7});
  Matrix<int64_t> matrix({{1, 4, 7, 1}, {2, 5, 8, 3}, {3, 6, 9, 4}});
  Matrix<int64_t> matrix_expected({{38, 92, 146, 51}});
  auto res = vector.Product(matrix);
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, InverseMatrix) {
  Matrix<int> matrix({{0, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<double> matrix_expected(
      {{-1, 2, -1}, {2, -7, 4}, {-1, 4.66667, -2.66667}});
  auto res = matrix.Inverse();
  EXPECT_TRUE((matrix_expected - res).AllElementsLess(10e-5));
}