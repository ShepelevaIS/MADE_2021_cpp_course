#include <gtest/gtest.h>
#include <matrix_calculator.h>

#include <vector>

TEST(VectorTest, EmptyVector) {
  Vector<float> vector;
  EXPECT_EQ(0, vector.Size());
}

TEST(VectorTest, VectorCreateWith) {
  Vector<float> vector({1, 2, 4}, Vector<float>::Type::ROW);
  EXPECT_FLOAT_EQ(4, vector[2]);
}

TEST(VectorTest, VectorCreateFromVector) {
  std::vector<float> std_vector{1, 3, 4};
  Vector<float> vector(std_vector.data(), std_vector.size());
  EXPECT_FLOAT_EQ(4, vector[2]);
}

TEST(VectorTest, VectorCreate) {
  float arr[] = {1, 2, 3, 4, 5};
  Vector<float> vector(arr, 5, Vector<float>::Type::COLUMN);
  EXPECT_FLOAT_EQ(5, vector[4]);
}

TEST(VectorTest, VectorAssignment) {
  Vector<float> vector;
  Vector<float> vector_other = {1, 2, 3, 4, 5};
  Vector<float> vector_expected = {1, 2, 3, 4, 5};
  vector = vector_other;
  EXPECT_EQ(vector_expected, vector);
}

TEST(VectorTest, SumVectors) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_second({5, 6, 7});
  Vector<float> vector_expected({6, 8, 11});
  auto vector = vector_first + vector_second;
  EXPECT_EQ(3, vector.Size());
  for (size_t i = 0; i < vector.Size(); ++i) {
    EXPECT_EQ(vector_expected[i], vector[i]);
  }
}

TEST(VectorTest, VectorEqual) {
  Vector<float> vector_first = {1, 2, 3};
  Vector<float> vector_second = {1, 2, 3, 4};
  EXPECT_FALSE(vector_first == vector_second);
}

TEST(VectorTest, VectorAtConst) {
  const Vector<float> vector = {1, 2, 3};
  float expected = 1;
  EXPECT_EQ(expected, vector.At(0));
}

TEST(VectorTest, VectorTranspose) {
  Vector<float> vector = {1, 2, 3};
  Vector<float> vector_expected({1, 2, 3}, Vector<float>::Type::COLUMN);
  Vector<float> vector_transposed = vector.Transpose();
  EXPECT_EQ(vector_expected, vector_transposed);
}

TEST(VectorTest, SumVectorsThrowSize) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_second({5, 6, 7, 8});
  EXPECT_THROW({ auto vector = vector_first + vector_second; }, const char *);
}

TEST(VectorTest, SumVectorsThrowType) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_second({5, 6, 7}, Vector<float>::Type::COLUMN);
  EXPECT_THROW({ auto vector = vector_first + vector_second; }, const char *);
}

TEST(VectorTest, SubtractVectors) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_second({5, 6, 7});
  Vector<float> vector_expected({-4, -4, -3});
  auto vector = vector_first - vector_second;
  EXPECT_EQ(vector_expected, vector);
}

TEST(VectorTest, SubtractVectorsThrowSize) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_second({5, 6, 7, 8});
  EXPECT_THROW({ auto vector = vector_first - vector_second; }, const char *);
}

TEST(VectorTest, SubtractVectorsThrowType) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_second({5, 6, 7}, Vector<float>::Type::COLUMN);
  EXPECT_THROW({ auto vector = vector_first - vector_second; }, const char *);
}

TEST(VectorTest, VectorElementwiseProduct) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_second({5, 6, 7});
  Vector<float> vector_expected({5, 12, 28});
  auto vector = vector_first * vector_second;
  EXPECT_EQ(vector_expected, vector);
}

TEST(VectorTest, VectorElementwiseProductThrowSize) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_second({5, 6, 7, 8});
  EXPECT_THROW({ auto vector = vector_first * vector_second; }, const char *);
}

TEST(VectorTest, VectorElementwiseProductThrowType) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_second({5, 6, 7}, Vector<float>::Type::COLUMN);
  EXPECT_THROW({ auto vector = vector_first * vector_second; }, const char *);
}

TEST(VectorTest, VectorAdditionAssignment) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_second({5, 6, 7});
  Vector<float> vector_expected({6, 8, 11});
  vector_first += vector_second;
  EXPECT_EQ(vector_expected, vector_first);
}

TEST(VectorTest, VectorSubtractionAssignment) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_second({5, 6, 7});
  Vector<float> vector_expected({-4, -4, -3});
  vector_first -= vector_second;
  EXPECT_EQ(vector_expected, vector_first);
}

TEST(VectorTest, VectorMultiplyAssignment) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_second({5, 6, 7});
  Vector<float> vector_expected({5, 12, 28});
  vector_first *= vector_second;
  EXPECT_EQ(vector_expected, vector_first);
}

TEST(VectorTest, VectorSumNumber) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_expected({5, 6, 8});
  auto vector = vector_first + 4;
  EXPECT_EQ(vector_expected, vector);
}

TEST(VectorTest, VectorSumNumberLeft) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_expected({5, 6, 8});
  auto vector = static_cast<float>(4) + vector_first;
  EXPECT_EQ(vector_expected, vector);
}

TEST(VectorTest, VectorSubstractNumber) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_expected({-4, -3, -1});
  auto vector = vector_first - 5;
  EXPECT_EQ(vector_expected, vector);
}

TEST(VectorTest, VectorSubtractNumberLeft) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_expected({4, 3, 1});
  auto vector = static_cast<float>(5) - vector_first;
  EXPECT_EQ(vector_expected, vector);
}

TEST(VectorTest, VectorMultiplyNumber) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_expected({3, 6, 12});
  auto vector = vector_first * 3;
  EXPECT_EQ(vector_expected, vector);
}

TEST(VectorTest, VectorMultiplyNumberLeft) {
  Vector<float> vector_first({1, 2, 4}, Vector<float>::Type::ROW);
  Vector<float> vector_expected({3, 6, 12});
  auto vector = static_cast<float>(3) * vector_first;
  EXPECT_EQ(vector_expected, vector);
}

TEST(MatrixTest, MatrixCreate) {
  Matrix<float> matrix(5, 6);
  matrix.At(0, 0) = 1337;
  EXPECT_FLOAT_EQ(1337, matrix[0][0]);
}

TEST(MatrixTest, GeColumn) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector_expected({3, 6, 9}, Vector<float>::Type::COLUMN);
  auto res = matrix.GetColumn(2);
  EXPECT_EQ(vector_expected, res);
}

TEST(MatrixTest, GetAnotherColumn) {
  Matrix<float> matrix({{1, 2}, {4, 5}, {7, 8}});
  Vector<float> vector_expected({1, 4, 7}, Vector<float>::Type::COLUMN);
  auto res = matrix.GetColumn(0);
  EXPECT_EQ(vector_expected, res);
}

TEST(MatrixTest, MatrixFromVectors) {
  Matrix<float> matrix(
      {Vector<float>{1, 2, 3}, Vector<float>{4, 5, 6}, Vector<float>{7, 8, 9}});
  Matrix<float> matrix_expected({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  EXPECT_EQ(matrix_expected, matrix);
}

TEST(MatrixTest, MatrixPlusMatrix) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<float> matrix_second({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<float> matrix_expected({{2, 4, 6}, {8, 10, 12}, {14, 16, 18}});
  auto res = matrix_first + matrix_second;
  EXPECT_EQ(3, res.RowSize());
  EXPECT_EQ(3, res.ColSize());
  for (size_t i = 0; i < res.RowSize(); ++i) {
    for (size_t j = 0; j < res.ColSize(); ++j) {
      EXPECT_EQ(matrix_expected[i][j], res[i][j]);
    }
  }
}

TEST(MatrixTest, MatrixNotEqual) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<float> matrix_second({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});
  EXPECT_FALSE(matrix_first == matrix_second);
}

TEST(MatrixTest, MatrixPlusMatrixThrowSize) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<float> matrix_second({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});
  EXPECT_THROW({ auto res = matrix_first + matrix_second; }, const char *);
}

TEST(MatrixTest, MatrixPlusNumber) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  float number = 1;
  Matrix<float> matrix_expected({{2, 3, 4}, {5, 6, 7}, {8, 9, 10}});
  auto res = matrix_first + number;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixPlusVectorRow) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector{1, 2, 3};
  Matrix<float> matrix_expected({{2, 4, 6}, {5, 7, 9}, {8, 10, 12}});
  auto res = matrix + vector;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixPlusVectorRowThrowSize) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector{1, 2, 3, 4};
  EXPECT_THROW({ auto res = matrix + vector; }, const char *);
}

TEST(MatrixTest, MatrixPlusVectorColumn) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector({1, 2, 3}, Vector<float>::Type::COLUMN);
  Matrix<float> matrix_expected({{2, 3, 4}, {6, 7, 8}, {10, 11, 12}});
  auto res = matrix + vector;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixPlusVectorColumnThrowSize) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector({1, 2, 3, 4}, Vector<float>::Type::COLUMN);
  EXPECT_THROW({ auto res = matrix + vector; }, const char *);
}

TEST(MatrixTest, MatrixPlusVectorRowLeft) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector{1, 2, 3};
  Matrix<float> matrix_expected({{2, 4, 6}, {5, 7, 9}, {8, 10, 12}});
  auto res = vector + matrix;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixPlusVectorColumnLeft) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector({1, 2, 3}, Vector<float>::Type::COLUMN);
  Matrix<float> matrix_expected({{2, 3, 4}, {6, 7, 8}, {10, 11, 12}});
  auto res = vector + matrix;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixPlusNumberLeft) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  float number = 1;
  Matrix<float> matrix_expected({{2, 3, 4}, {5, 6, 7}, {8, 9, 10}});
  auto res = number + matrix_first;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMinusMatrix) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<float> matrix_second({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<float> matrix_expected({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
  auto res = matrix_first - matrix_second;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMinusMatrixThrowSize) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<float> matrix_second({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});
  EXPECT_THROW({ auto res = matrix_first - matrix_second; }, const char *);
}

TEST(MatrixTest, MatrixMinusNumber) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  float number = -1;
  Matrix<float> matrix_expected({{2, 3, 4}, {5, 6, 7}, {8, 9, 10}});
  auto res = matrix_first - number;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMinusVectorRow) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector{1, 2, 3};
  Matrix<float> matrix_expected({{0, 0, 0}, {3, 3, 3}, {6, 6, 6}});
  auto res = matrix - vector;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMinusVectorRowThrowSize) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector{1, 2, 3, 4};
  EXPECT_THROW({ auto res = matrix - vector; }, const char *);
}

TEST(MatrixTest, MatrixMinusVectorRowLeft) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector{1, 2, 3};
  Matrix<float> matrix_expected({{0, 0, 0}, {-3, -3, -3}, {-6, -6, -6}});
  auto res = vector - matrix;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMinusVectorRowLeftThrowSize) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector{1, 2, 3, 4};
  EXPECT_THROW({ auto res = vector - matrix; }, const char *);
}

TEST(MatrixTest, MatrixMinusVectorColumn) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector({1, 2, 3}, Vector<float>::Type::COLUMN);
  Matrix<float> matrix_expected({{0, 1, 2}, {2, 3, 4}, {4, 5, 6}});
  auto res = matrix - vector;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMinusVectorColumnThrowSize) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector({1, 2, 3, 4}, Vector<float>::Type::COLUMN);
  EXPECT_THROW({ auto res = matrix - vector; }, const char *);
}

TEST(MatrixTest, MatrixMinusVectorColumnLeft) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector({1, 2, 3}, Vector<float>::Type::COLUMN);
  Matrix<float> matrix_expected({{0, -1, -2}, {-2, -3, -4}, {-4, -5, -6}});
  auto res = vector - matrix;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMinusVectorColumnLeftThrowSize) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector({1, 2, 3, 4}, Vector<float>::Type::COLUMN);
  EXPECT_THROW({ auto res = vector - matrix; }, const char *);
}

TEST(MatrixTest, MatrixMinusNumberLeft) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  float number = -1;
  Matrix<float> matrix_expected({{-2, -3, -4}, {-5, -6, -7}, {-8, -9, -10}});
  auto res = number - matrix_first;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMultiplyMatrix) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<float> matrix_second({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<float> matrix_expected({{1, 4, 9}, {16, 25, 36}, {49, 64, 81}});
  auto res = matrix_first * matrix_second;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMultiplyMatrixThrowSize) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<float> matrix_second({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});
  EXPECT_THROW({ auto res = matrix_first * matrix_second; }, const char *);
}

TEST(MatrixTest, MatrixMultiplyNumber) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  float number = 2;
  Matrix<float> matrix_expected({{2, 4, 6}, {8, 10, 12}, {14, 16, 18}});
  auto res = matrix_first * number;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMultiplyNumberLeft) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  float number = 2;
  Matrix<float> matrix_expected({{2, 4, 6}, {8, 10, 12}, {14, 16, 18}});
  auto res = number * matrix_first;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMultiplyVectorRowLeft) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector({1, 2, 3});
  Matrix<float> matrix_expected({{1, 4, 9}, {4, 10, 18}, {7, 16, 27}});
  auto res = vector * matrix;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMultiplyVectorRowLeftThrowSize) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector({1, 2, 3, 4});
  EXPECT_THROW({ auto res = vector * matrix; }, const char *);
}

TEST(MatrixTest, MatrixMultiplyVectorColumnLeft) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector({1, 2, 3}, Vector<float>::Type::COLUMN);
  Matrix<float> matrix_expected({{1, 2, 3}, {8, 10, 12}, {21, 24, 27}});
  auto res = vector * matrix;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMultiplyVectorColumnLeftThrowSize) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector({1, 2, 3, 4}, Vector<float>::Type::COLUMN);
  EXPECT_THROW({ auto res = vector * matrix; }, const char *);
}

TEST(MatrixTest, MatrixMultiplyVector) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector({1, 2, 3}, Vector<float>::Type::COLUMN);
  Matrix<float> matrix_expected({{1, 2, 3}, {8, 10, 12}, {21, 24, 27}});
  auto res = matrix * vector;
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, GetDiagonal) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Vector<float> vector_expected({1, 5, 9});
  auto res = matrix.GetDiagonal();
  EXPECT_EQ(vector_expected, res);
}

TEST(MatrixTest, GetDiagonalRectangle) {
  Matrix<float> matrix({{1, 2}, {4, 5}, {7, 8}});
  Vector<float> vector_expected({1, 5});
  auto res = matrix.GetDiagonal();
  EXPECT_EQ(vector_expected, res);
}

TEST(MatrixTest, TransposeMatrix) {
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 3, 4}});
  Matrix<float> matrix_expected({{1, 4, 7, 1}, {2, 5, 8, 3}, {3, 6, 9, 4}});
  auto res = matrix.Transpose();
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMatrixProduct) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 3, 4}});
  Matrix<float> matrix_second({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<float> matrix_expected(
      {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}, {41, 49, 57}});
  auto res = matrix_first.Product(matrix_second);
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixMatrixProductThrowSize) {
  Matrix<float> matrix_first({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 3, 4}});
  Matrix<float> matrix_second({{1, 2, 3}, {4, 5, 6}});
  EXPECT_THROW({ auto res = matrix_first.Product(matrix_second); },
               const char *);
}

TEST(MatrixTest, MatrixVectorProductColumn) {
  Vector<float> vector({5, 6, 7}, Vector<float>::Type::COLUMN);
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 3, 4}});
  Matrix<float> matrix_expected = {{38}, {92}, {146}, {51}};
  auto res = matrix.Product(vector);
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixVectorProductColumnThrowSize) {
  Vector<float> vector({5, 6}, Vector<float>::Type::COLUMN);
  Matrix<float> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 3, 4}});
  EXPECT_THROW({ auto res = matrix.Product(vector); }, const char *);
}

TEST(MatrixTest, MatrixVectorProductRow) {
  Vector<float> vector({5, 6, 7});
  Matrix<float> matrix({{1}, {2}, {3}});
  Matrix<float> matrix_expected = {{5, 6, 7}, {10, 12, 14}, {15, 18, 21}};
  auto res = matrix.Product(vector);
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixVectorProductRowThrowSize) {
  Vector<float> vector({5, 6, 7});
  Matrix<float> matrix({{1, 2}, {2, 3}, {3, 4}});
  EXPECT_THROW({ auto res = matrix.Product(vector); }, const char *);
}

TEST(MatrixTest, VectorMatrixProduct) {
  Vector<float> vector({5, 6, 7});
  Matrix<float> matrix({{1, 4, 7, 1}, {2, 5, 8, 3}, {3, 6, 9, 4}});
  Matrix<float> matrix_expected({{38, 92, 146, 51}});
  auto res = vector.Product(matrix);
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, ColumnVectorMatrixProduct) {
  Vector<float> vector({5, 6, 7}, Vector<float>::Type::COLUMN);
  Matrix<float> matrix({{1, 4, 7, 1}});
  Matrix<float> matrix_expected({{5 * 1, 5 * 4, 5 * 7, 5 * 1},
                                 {6 * 1, 6 * 4, 6 * 7, 6 * 1},
                                 {7 * 1, 7 * 4, 7 * 7, 7 * 1}});
  auto res = vector.Product(matrix);
  EXPECT_EQ(matrix_expected, res);
}

TEST(MatrixTest, MatrixDet) {
  Matrix<int> matrix({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
  int det = matrix.Det();
  EXPECT_EQ(0, det);
}

TEST(MatrixTest, MatrixDetThrowSize) {
  Matrix<int> matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});
  EXPECT_THROW({ int det = matrix.Det(); }, const char *);
}

TEST(MatrixTest, InverseMatrix) {
  Matrix<int> matrix({{0, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix<double> matrix_expected(
      {{-1, 2, -1}, {2, -7, 4}, {-1, 4.66667, -2.66667}});
  auto res = matrix.Inverse();
  EXPECT_TRUE((matrix_expected - res).AllElementsLess(10e-5));
}

TEST(MatrixTest, InverseMatrixThrowSize) {
  Matrix<int> matrix({{0, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}});
  EXPECT_THROW({ auto res = matrix.Inverse(); }, const char *);
}

TEST(MatrixTest, InverseMatrixThrowDetZero) {
  Matrix<int> matrix({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
  EXPECT_THROW({ auto res = matrix.Inverse(); }, const char *);
}
