#ifndef HOME_TASK_2_MATRIX_CALCULATOR_LIB_MATRIX_CALCULATOR_H_
#define HOME_TASK_2_MATRIX_CALCULATOR_LIB_MATRIX_CALCULATOR_H_

#include <algorithm>
#include <cassert>
#include <cstring>
#include <optional>

template <typename Data> class Matrix;

template <typename Data> class Vector {
public:  // NOLINT
  enum class Type { ROW, COLUMN };

  Vector() : size_(0), values_(nullptr), type_(Type::ROW) {}

  explicit Vector(size_t size, Type type = Type::ROW)
      : size_(size), values_(size ? new Data[size]{} : nullptr), type_(type) {
    std::memset(values_, 0, sizeof(Data) * size_);
  }

  Vector(const Data *values, size_t size, Type type = Type::ROW)
      : Vector(size, type) {
    for (size_t i = 0; i < size_; ++i) {
      values_[i] = values[i];
    }
  }

  Vector(const Vector<Data> &other) : Vector(other.size_, other.type_) {
    std::copy(other.values_, other.values_ + other.size_, values_);
  }

  Vector(std::initializer_list<Data> values, Type type = Type::ROW)
      : Vector(values.size(), type) {
    std::copy(values.begin(), values.end(), values_);
  }

  ~Vector() {
    if (values_) {
      delete[] values_;
    }
  }

  Vector<Data> &operator=(const Vector<Data> &other) {
    if (this != &other) {
      Vector<Data>(other).Swap(*this);
    }
    return *this;
  }

  bool operator==(const Vector<Data> &other) const {
    if (Size() != other.Size()) {
      return false;
    }
    return std::equal(values_, values_ + size_, other.values_);
  }

  const Data &operator[](size_t index) const { return values_[index]; }

  Vector<Data> &operator+=(const Vector<Data> &other) {
    if (size_ != other.size_) {
      throw "Size mismatch";
    }
    if (type_ != other.type_) {
      throw "Type mismatch";
    }
    for (size_t i = 0; i < Size(); ++i) {
      values_[i] += other.values_[i];
    }
    return *this;
  }

  Vector<Data> operator+(const Vector<Data> &other) const {
    Vector<Data> result(*this);
    result += other;
    return result;
  }

  Vector<Data> &operator+=(const Data &data) {
    for (size_t i = 0; i < size_; ++i) {
      values_[i] += data;
    }
    return *this;
  }

  Vector<Data> operator+(const Data &data) const {
    Vector result(*this);
    result += data;
    return result;
  }

  Matrix<Data> operator+(const Matrix<Data> &matrix) const {
    Matrix<Data> result(matrix);
    result += *this;
    return result;
  }

  Vector<Data> &operator-=(const Vector<Data> &other) {
    if (size_ != other.size_) {
      throw "Size mismatch";
    }
    if (type_ != other.type_) {
      throw "Type mismatch";
    }
    for (size_t i = 0; i < Size(); ++i) {
      values_[i] -= other.values_[i];
    }
    return *this;
  }

  Vector<Data> operator-(const Vector<Data> &other) const {
    Vector<Data> result(*this);
    result -= other;
    return result;
  }

  Vector<Data> &operator-=(const Data &data) {
    for (size_t i = 0; i < size_; ++i) {
      values_[i] -= data;
    }
    return *this;
  }

  Vector<Data> operator-(const Data &data) const {
    Vector result(*this);
    result -= data;
    return result;
  }

  Matrix<Data> operator-(const Matrix<Data> &matrix) const {
    if (IsRow()) {
      if (Size() != matrix.ColSize()) {
        throw "Size mismatch";
      }
      Matrix<Data> result(matrix.RowSize(), matrix.ColSize());
      for (size_t i = 0; i < matrix.RowSize(); ++i) {
        for (size_t j = 0; j < matrix.ColSize(); ++j) {
          result.At(i, j) = values_[j] - matrix[i][j];
        }
      }
      return result;
    }
    if (Size() != matrix.RowSize()) {
      throw "Size mismatch";
    }
    Matrix<Data> result(matrix.RowSize(), matrix.ColSize());
    for (size_t i = 0; i < matrix.RowSize(); ++i) {
      for (size_t j = 0; j < matrix.ColSize(); ++j) {
        result.At(i, j) = values_[i] - matrix[i][j];
      }
    }
    return result;
  }

  Vector<Data> &operator*=(const Vector<Data> &other) {
    if (size_ != other.size_) {
      throw "size mismatch";
    }
    if (type_ != other.type_) {
      throw "Type mismatch";
    }
    for (size_t i = 0; i < Size(); ++i) {
      values_[i] *= other.values_[i];
    }
    return *this;
  }

  Vector<Data> operator*(const Vector<Data> &other) const {
    Vector<Data> result(*this);
    result *= other;
    return result;
  }

  Vector<Data> &operator*=(const Data &data) {
    for (size_t i = 0; i < size_; ++i) {
      values_[i] *= data;
    }
    return *this;
  }

  Vector<Data> operator*(const Data &data) const {
    Vector result(*this);
    result *= data;
    return result;
  }

  Matrix<Data> operator*(const Matrix<Data> &matrix) const {
    Matrix<Data> result(matrix);
    result *= *this;
    return result;
  }

  Data &At(size_t index) { return values_[index]; }

  const Data &At(size_t index) const { return values_[index]; }

  size_t Size() const { return size_; }

  bool IsRow() const { return type_ == Type::ROW; }

  Matrix<Data> Product(const Matrix<Data> &matrix) const {
    if (IsRow()) {
      Matrix<Data> result(1, matrix.ColSize());
      for (size_t j = 0; j < result.ColSize(); ++j) {
        for (size_t k = 0; k < matrix.RowSize(); ++k) {
          result.At(0, j) += values_[k] * matrix.At(k, j);
        }
      }
      return result;
    }
    Matrix<Data> result(Size(), matrix.ColSize());
    for (size_t i = 0; i < result.RowSize(); ++i) {
      for (size_t j = 0; j < result.ColSize(); ++j) {
        result.At(i, j) = values_[i] * matrix.At(0, j);
      }
    }
    return result;
  }

  Vector<Data> Transpose() const {
    Vector<Data> result(*this);
    result.type_ = (type_ == Type::ROW) ? Type::COLUMN : Type::ROW;
    return result;
  }

  void Swap(Vector<Data> &other) {
    std::swap(values_, other.values_);
    std::swap(size_, other.size_);
    std::swap(type_, other.type_);
  }

private:  // NOLINT
  size_t size_;
  Data *values_;
  Type type_;
};

template <typename Data>
Vector<Data> operator+(const Data &data, const Vector<Data> &other) {
  return other + data;
}

template <typename Data>
Vector<Data> operator-(const Data &data, const Vector<Data> &other) {
  Vector<Data> result(other.Size());
  for (size_t i = 0; i < result.Size(); ++i) {
    result.At(i) = data - other[i];
  }
  return result;
}

template <typename Data>
Vector<Data> operator*(const Data &data, const Vector<Data> &other) {
  return other * data;
}

template <typename Data> class Matrix {
public:  // NOLINT
  Matrix(size_t row_size, size_t col_size)
      : row_size_(row_size), col_size_(col_size),
        values_(new Data[row_size * col_size]) {
    std::memset(values_, 0, sizeof(Data) * row_size_ * col_size_);
  }

  Matrix(std::initializer_list<std::initializer_list<Data>> values)
      : Matrix(values.size(), values.begin()->size()) {
    size_t idx = 0;
    for (const auto &value : values) {
      std::copy(value.begin(), value.end(), values_ + idx * col_size_);
      ++idx;
    }
  }

  Matrix(std::initializer_list<Vector<Data>> values)
      : Matrix(values.size(), values.begin()->Size()) {
    size_t idx = 0;
    for (const auto &value : values) {
      for (size_t i = 0; i < value.Size(); ++i) {
        At(idx, i) = value[i];
      }
      ++idx;
    }
  }

  const Data *operator[](size_t index) const {
    return values_ + index * col_size_;
  }

  bool operator==(const Matrix<Data> &other) const {
    if (RowSize() != other.RowSize() || ColSize() != other.ColSize()) {
      return false;
    }
    return std::equal(values_, values_ + row_size_ * col_size_, other.values_);
  }

  Matrix<Data> &operator+=(const Matrix<Data> &other) {
    if (RowSize() != other.RowSize() || ColSize() != other.ColSize()) {
      throw "Size mismatch";
    }
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        At(i, j) += other.At(i, j);
      }
    }
    return *this;
  }

  Matrix<Data> operator+(const Matrix<Data> &other) const {
    Matrix<Data> result(*this);
    result += other;
    return result;
  }

  Matrix<Data> &operator+=(const Data &data) {
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        At(i, j) += data;
      }
    }
    return *this;
  }

  Matrix<Data> operator+(const Data &other) const {
    Matrix<Data> result(*this);
    result += other;
    return result;
  }

  Matrix<Data> &operator+=(const Vector<Data> &vector) {
    if (vector.IsRow()) {
      if (ColSize() != vector.Size()) {
        throw "Size mismath";
      }
      for (size_t i = 0; i < RowSize(); ++i) {
        for (size_t j = 0; j < ColSize(); ++j) {
          At(i, j) += vector[j];
        }
      }
      return *this;
    }
    if (RowSize() != vector.Size()) {
      throw "Size mismatch";
    }
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        At(i, j) += vector[i];
      }
    }
    return *this;
  }

  Matrix<Data> operator+(const Vector<Data> &vector) const {
    Matrix<Data> result(*this);
    result += vector;
    return result;
  }

  Matrix<Data> &operator-=(const Matrix<Data> &other) {
    if (RowSize() != other.RowSize() || ColSize() != other.ColSize()) {
      throw "Size mismatch";
    }
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        At(i, j) -= other.At(i, j);
      }
    }
    return *this;
  }

  Matrix<Data> operator-(const Matrix<Data> &other) const {
    Matrix<Data> result(*this);
    result -= other;
    return result;
  }

  Matrix<Data> &operator-=(const Data &data) {
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        At(i, j) -= data;
      }
    }
    return *this;
  }

  Matrix<Data> operator-(const Data &other) const {
    Matrix<Data> result(*this);
    result -= other;
    return result;
  }

  Matrix<Data> operator-=(const Vector<Data> &vector) {
    if (vector.IsRow()) {
      if (ColSize() != vector.Size()) {
        throw "Size mismath";
      }
      for (size_t i = 0; i < RowSize(); ++i) {
        for (size_t j = 0; j < ColSize(); ++j) {
          At(i, j) -= vector[j];
        }
      }
      return *this;
    }
    if (RowSize() != vector.Size()) {
      throw "Size mismatch";
    }
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        At(i, j) -= vector[i];
      }
    }
    return *this;
  }

  Matrix<Data> operator-(const Vector<Data> &vector) const {
    Matrix<Data> result(*this);
    result -= vector;
    return result;
  }

  Matrix<Data> &operator*=(const Matrix<Data> &other) {
    if (RowSize() != other.RowSize() || ColSize() != other.ColSize()) {
      throw "Size mismatch";
    }
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        At(i, j) *= other.At(i, j);
      }
    }
    return *this;
  }

  Matrix<Data> operator*(const Matrix<Data> &other) const {
    Matrix<Data> result(*this);
    result *= other;
    return result;
  }

  Matrix<Data> &operator*=(const Data &data) {
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        At(i, j) *= data;
      }
    }
    return *this;
  }

  Matrix<Data> operator*(const Data &other) const {
    Matrix<Data> result(*this);
    result *= other;
    return result;
  }

  Matrix<Data> &operator*=(const Vector<Data> &vector) {
    if (vector.IsRow()) {
      if (ColSize() != vector.Size()) {
        throw "Size mismath";
      }
      for (size_t i = 0; i < RowSize(); ++i) {
        for (size_t j = 0; j < ColSize(); ++j) {
          At(i, j) *= vector[j];
        }
      }
      return *this;
    }
    if (RowSize() != vector.Size()) {
      throw "Size mismatch";
    }
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        At(i, j) *= vector[i];
      }
    }
    return *this;
  }

  Matrix<Data> operator*(const Vector<Data> &vector) const {
    Matrix<Data> result(*this);
    result *= vector;
    return result;
  }

  Data &At(size_t row, size_t col) { return values_[row * col_size_ + col]; }

  const Data &At(size_t row, size_t col) const {
    return values_[row * col_size_ + col];
  }

  void Swap(size_t first_row, size_t second_row) {
    for (size_t i = 0; i < ColSize(); ++i) {
      std::swap(At(first_row, i), At(second_row, i));
    }
  }

  size_t ColSize() const { return col_size_; }

  size_t RowSize() const { return row_size_; }

  Vector<Data> GetColumn(size_t index) const {
    Vector<Data> result(RowSize());
    for (size_t i = 0; i < RowSize(); ++i) {
      result.At(i) = At(i, index);
    }
    return result;
  }

  Vector<Data> GetDiagonal() const {
    size_t result_size = std::min(RowSize(), ColSize());
    Vector<Data> result(result_size);
    for (size_t i = 0; i < result_size; ++i) {
      result.At(i) = At(i, i);
    }
    return result;
  }

  Matrix<Data> Transpose() const {
    Matrix<Data> result(ColSize(), RowSize());
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        result.At(j, i) = At(i, j);
      }
    }
    return result;
  }

  Matrix<Data> Product(const Matrix &matrix) const {
    if (ColSize() != matrix.RowSize()) {
      throw "Size mismatch";
    }
    Matrix<Data> result(RowSize(), matrix.ColSize());
    for (size_t i = 0; i < result.RowSize(); ++i) {
      for (size_t j = 0; j < result.ColSize(); ++j) {
        for (size_t k = 0; k < ColSize(); ++k) {
          result.At(i, j) += At(i, k) * matrix.At(k, j);
        }
      }
    }
    return result;
  }

  Matrix<Data> Product(const Vector<Data> &vector) const {
    if (vector.IsRow()) {
      if (ColSize() != 1) {
        throw "Size mismatch";
      }
      Matrix<Data> result(RowSize(), vector.Size());
      for (size_t i = 0; i < RowSize(); ++i) {
        for (size_t j = 0; j < vector.Size(); ++j) {
          result.At(i, j) = At(i, 0) * vector[j];
        }
      }
      return result;
    } else {
      if (ColSize() != vector.Size()) {
        throw "Size mismatch";
      }
      Matrix<Data> result(RowSize(), 1);
      for (size_t i = 0; i < result.RowSize(); ++i) {
        for (size_t k = 0; k < ColSize(); ++k) {
          result.At(i, 0) += At(i, k) * vector[k];
        }
      }
      return result;
    }
  }

  Data Det() const {
    if (RowSize() != ColSize()) {
      throw "Size mismatch";
    }
    Matrix<Data> triangle(*this);
    Data det_divisor = 1;
    for (size_t i = 0; i + 1 < RowSize(); ++i) {
      if (triangle.At(i, i) == 0) {
        for (size_t k = i + 1; k < RowSize(); ++k) {
          if (triangle.At(k, i) != 0) {
            triangle.Swap(i, k);
            det_divisor = -det_divisor;
            break;
          }
        }
        if (triangle.At(i, i) == 0) {
          return 0;
        }
      }
      for (size_t k = i + 1; k < RowSize(); ++k) {
        det_divisor *= triangle.At(i, i);
        Data alpha = triangle.At(k, i);
        for (size_t j = i; j < RowSize(); ++j) {
          triangle.At(k, j) =
              triangle.At(i, i) * triangle.At(k, j) - alpha * triangle.At(i, j);
        }
      }
    }
    Data diag = triangle.At(0, 0);
    for (int i = 1; i < RowSize(); ++i) {
      diag *= triangle.At(i, i);
    }
    return diag / det_divisor;
  }

  Matrix<Data> GetMinor(size_t row, size_t col) const {
    Matrix<Data> result(RowSize() - 1, ColSize() - 1);
    for (size_t i = 0; i < RowSize(); ++i) {
      if (i == row) {
        continue;
      }
      size_t minor_i = (i < row) ? i : i - 1;
      for (size_t j = 0; j < ColSize(); ++j) {
        if (j == col) {
          continue;
        }
        size_t minor_j = (j < col) ? j : j - 1;
        result.At(minor_i, minor_j) = At(i, j);
      }
    }
    return result;
  }

  Matrix<double> Inverse() const {
    if (RowSize() != ColSize()) {
      throw "Size mismatch";
    }
    Matrix<double> result(RowSize(), ColSize());
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        result.At(i, j) = GetMinor(i, j).Det();
        if ((i + j) % 2 == 1) {
          result.At(i, j) = -result.At(i, j);
        }
      }
    }
    auto det = Det();
    if (det == 0) {
      throw "Zero determinant";
    }
    return result.Transpose() * (1. / det);
  }

  bool AllElementsLess(double abs_err) {
    return std::all_of(
        values_, values_ + row_size_ * col_size_,
        [&abs_err](const Data &data) { return std::abs(data) < abs_err; });
  }

private:  // NOLINT
  size_t row_size_;
  size_t col_size_;
  Data *values_;
};

template <typename Data>
Matrix<Data> operator+(const Data &data, const Matrix<Data> &other) {
  return other + data;
}

template <typename Data>
Matrix<Data> operator-(const Data &data, const Matrix<Data> &other) {
  Matrix<Data> result(other.RowSize(), other.ColSize());
  for (size_t i = 0; i < result.RowSize(); ++i) {
    for (size_t j = 0; j < result.ColSize(); ++j) {
      result.At(i, j) = data - other[i][j];
    }
  }
  return result;
}

template <typename Data>
Matrix<Data> operator*(const Data &data, const Matrix<Data> &other) {
  return other * data;
}

#endif  // HOME_TASK_2_MATRIX_CALCULATOR_LIB_MATRIX_CALCULATOR_H_
