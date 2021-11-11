#ifndef MATRIX_CALCULATOR_H
#define MATRIX_CALCULATOR_H

#include <algorithm>
#include <cassert>

template <typename Data> class Matrix;

template <typename Data> class Vector {
public:
  Vector() : size_(0), values_(nullptr), is_row_(true) {}

  Vector(const Data *values, size_t size, bool is_row = true)
      : size_(size), is_row_(is_row) {
    values_ = (size_ == 0) ? nullptr : new Data[size_];
    for (size_t i = 0; i < size_; ++i) {
      values_[i] = values[i];
    }
  }

  Vector(size_t size, bool is_row = true) : size_(size), is_row_(is_row) {
    values_ = (size_ == 0) ? nullptr : new Data[size_];
  }

  Vector(const Vector<Data> &other)
      : size_(other.size_), is_row_(other.is_row_) {
    values_ = (size_ == 0) ? nullptr : new Data[size_];
    for (size_t i = 0; i < size_; ++i) {
      values_[i] = other.values_[i];
    }
  }

  Vector(std::initializer_list<Data> values, bool is_row = true)
      : size_(values.size()), is_row_(is_row) {
    values_ = (size_ == 0) ? nullptr : new Data[size_];
    size_t idx = 0;
    for (const auto &value : values) {
      values_[idx] = value;
      ++idx;
    }
  }

  ~Vector() {
    if (values_) {
      delete[] values_;
    }
  };

  Vector<Data> &operator=(const Vector<Data> &other) {
    if (this != &other) {
      Vector<Data>(other).Swap(*this);
    }
    return *this;
  }

  bool operator==(const Vector<Data> &other) const {
    if (Size() != other.Size()) {
      return false;
    } else {
      for (size_t i = 0; i < Size(); ++i) {
        if (values_[i] != other.values_[i]) {
          return false;
        }
      }
    }
    return true;
  }

  const Data &operator[](size_t index) const { return values_[index]; }

  Data &operator[](size_t index) { return values_[index]; }

  Vector<Data> &operator+=(const Vector<Data> &other) {
    assert(size_ == other.size_);
    assert(is_row_ == other.is_row_);
    for (size_t i = 0; i < Size(); ++i) {
      values_[i] += other.values_[i];
    }
    return *this;
  }

  Vector<Data> operator+(const Vector<Data> &other) const {
    assert(size_ == other.size_);
    assert(is_row_ == other.is_row_);
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

  Vector<Data> &operator-=(const Vector<Data> &other) {
    assert(size_ == other.size_);
    assert(is_row_ == other.is_row_);
    for (size_t i = 0; i < Size(); ++i) {
      values_[i] -= other.values_[i];
    }
    return *this;
  }

  Vector<Data> operator-(const Vector<Data> &other) const {
    assert(size_ == other.size_);
    assert(is_row_ == other.is_row_);
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

  Vector<Data> &operator*=(const Vector<Data> &other) {
    assert(size_ == other.size_);
    assert(is_row_ == other.is_row_);
    for (size_t i = 0; i < Size(); ++i) {
      values_[i] *= other.values_[i];
    }
    return *this;
  }

  Vector<Data> operator*(const Vector<Data> &other) const {
    assert(size_ == other.size_);
    assert(is_row_ == other.is_row_);
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

  size_t Size() const { return size_; }

  bool IsRow() const { return is_row_; }

  Matrix<Data> Product(const Matrix<Data> &matrix) const {
    return matrix.Transpose().Product(Transpose()).Transpose();
  }

  Vector<Data> Transpose() const {
    Vector<Data> result(*this);
    result.is_row_ = !is_row_;
    return result;
  }

  void Swap(Vector<Data> &other) {
    std::swap(values_, other.values_);
    std::swap(size_, other.size_);
    std::swap(is_row_, other.is_row_);
  }

private:
  size_t size_;
  Data *values_;
  bool is_row_;
};

template <typename Data> class Matrix {
public:
  Matrix(size_t row_size, size_t col_size) : values_(row_size) {
    for (size_t i = 0; i < row_size; ++i) {
      values_[i] = Vector<Data>(col_size);
    }
  }

  Matrix(std::initializer_list<std::initializer_list<Data>> values)
      : values_(values.size()) {
    size_t idx = 0;
    for (const auto &value : values) {
      values_[idx] = value;
      ++idx;
    }
  }

  const Vector<Data> &operator[](size_t index) const { return values_[index]; }

  Vector<Data> &operator[](size_t index) { return values_[index]; }

  bool operator==(const Matrix<Data> &other) const {
    if (RowSize() != other.RowSize() || ColSize() != other.ColSize()) {
      return false;
    } else {
      for (size_t i = 0; i < RowSize(); ++i) {
        if (!(values_[i] == other.values_[i])) {
          return false;
        }
      }
    }
    return true;
  }

  Matrix<Data> &operator+=(const Matrix<Data> &other) {
    assert(values_.Size() == other.values_.Size());
    assert(values_[0].Size() == other.values_[0].Size());
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        values_[i][j] += other.values_[i][j];
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
        values_[i][j] += data;
      }
    }
    return *this;
  }

  Matrix<Data> operator+(const Data &other) const {
    Matrix<Data> result(*this);
    result += other;
    return result;
  }

  Matrix<Data> &operator-=(const Matrix<Data> &other) {
    assert(values_.Size() == other.values_.Size());
    assert(values_[0].Size() == other.values_[0].Size());
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        values_[i][j] -= other.values_[i][j];
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
        values_[i][j] -= data;
      }
    }
    return *this;
  }

  Matrix<Data> operator-(const Data &other) const {
    Matrix<Data> result(*this);
    result -= other;
    return result;
  }

  Matrix<Data> &operator*=(const Matrix<Data> &other) {
    assert(values_.Size() == other.values_.Size());
    assert(values_[0].Size() == other.values_[0].Size());
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        values_[i][j] *= other.values_[i][j];
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
        values_[i][j] *= data;
      }
    }
    return *this;
  }

  Matrix<Data> operator*(const Data &other) const {
    Matrix<Data> result(*this);
    result *= other;
    return result;
  }

  size_t ColSize() const { return values_[0].Size(); }

  size_t RowSize() const { return values_.Size(); }

  Vector<Data> GetColumn(size_t index) const {
    Vector<Data> result(RowSize());
    for (size_t i = 0; i < RowSize(); ++i) {
      result[i] = values_[i][index];
    }
    return result;
  }

  Vector<Data> GetDiagonal(bool is_main = true) const {
    assert(values_.Size() == values_[0].Size());
    Vector<Data> result(RowSize());
    if (is_main) {
      for (size_t i = 0; i < RowSize(); ++i) {
        result[i] = values_[i][i];
      }
    } else {
      for (size_t i = 0; i < RowSize(); ++i) {
        result[i] = values_[i][ColSize() - i - 1];
      }
    }
    return result;
  }

  Matrix<Data> Transpose() const {
    Matrix<Data> result(ColSize(), RowSize());
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        result.values_[j][i] = values_[i][j];
      }
    }
    return result;
  }

  Matrix<Data> Product(const Matrix &matrix) const {
    assert(values_[0].Size() == matrix.values_.Size());
    Matrix<Data> result(RowSize(), matrix.ColSize());
    for (size_t i = 0; i < result.RowSize(); ++i) {
      for (size_t j = 0; j < result.ColSize(); ++j) {
        result.values_[i][j] = 0;
        for (size_t k = 0; k < ColSize(); ++k) {
          result.values_[i][j] += values_[i][k] * matrix.values_[k][j];
        }
      }
    }
    return result;
  }

  Matrix<Data> Product(const Vector<Data> &vector) const {
    if (vector.IsRow()) {
      assert(values_[0].Size() == 1);
      Matrix<Data> result(RowSize(), vector.Size());
      for (size_t i = 0; i < RowSize(); ++i) {
        for (size_t j = 0; j < vector.Size(); ++j) {
          result[i][j] = values_[i][0] * vector[j];
        }
      }
      return result;
    } else {
      assert(ColSize() == vector.Size());
      Matrix<Data> result(RowSize(), 1);
      for (size_t i = 0; i < result.RowSize(); ++i) {
        result[i][0] = 0;
        for (size_t k = 0; k < ColSize(); ++k) {
          result.values_[i][0] += values_[i][k] * vector[k];
        }
      }
      return result;
    }
  }

  Data Det() const {
    assert(RowSize() == ColSize());
    Matrix<Data> triangle(*this);
    Data det_divisor = 1;
    for (size_t i = 0; i + 1 < RowSize(); ++i) {
      if (triangle[i][i] == 0) {
        for (size_t k = i + 1; k < RowSize(); ++k) {
          if (triangle[k][i] != 0) {
            triangle[i].Swap(triangle[k]);
            det_divisor = -det_divisor;
            break;
          }
        }
        if (triangle[i][i] == 0) {
          return 0;
        }
      }
      for (size_t k = i + 1; k < RowSize(); ++k) {
        det_divisor *= triangle[i][i];
        Data alpha = triangle[k][i];
        for (size_t j = i; j < RowSize(); ++j) {
          triangle[k][j] =
              triangle[i][i] * triangle[k][j] - alpha * triangle[i][j];
        }
      }
    }
    Data diag = triangle[0][0];
    for (int i = 1; i < RowSize(); ++i) {
      diag *= triangle[i][i];
    }
    return diag / det_divisor;
  }

  Matrix<double> Inverse() const {
    assert(RowSize() == ColSize());
    Matrix<double> result(RowSize(), ColSize());
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        Matrix<double> minor(RowSize() - 1, ColSize() - 1);
        for (size_t u = 0; u < RowSize(); ++u) {
          if (u == i) {
            continue;
          }
          size_t x = (u < i) ? u : u - 1;
          for (size_t v = 0; v < ColSize(); ++v) {
            if (v == j) {
              continue;
            }
            size_t y = (v < j) ? v : v - 1;
            minor[x][y] = values_[u][v];
          }
        }
        result[i][j] = minor.Det();
        if ((i + j) % 2 == 1) {
          result[i][j] = -result[i][j];
        }
      }
    }
    return result.Transpose() * (1. / Det());
  }

  bool AllElementsLess(double abs_err) {
    for (size_t i = 0; i < RowSize(); ++i) {
      for (size_t j = 0; j < ColSize(); ++j) {
        if (std::abs(values_[i][j]) > abs_err) {
          return false;
        }
      }
    }
    return true;
  }

private:
  Vector<Vector<Data>> values_;
};

#endif // MATRIX_CALCULATOR_H