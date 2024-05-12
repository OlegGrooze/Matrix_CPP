#include "s21_matrix_oop.h"

// Конструктор по умолчанию
S21Matrix::S21Matrix() : S21Matrix(1, 1) {}

// Параметризованный конструктор
S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(new double[rows_ * cols_]{}) {
  if (rows < 1 || cols < 1) throw std::invalid_argument("INCORRECT MATRIX");
}

// Конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  std::copy(other.matrix_, other.matrix_ + other.rows_ * other.cols_, matrix_);
}

// Конструктор передачи
S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
}

// Деструктор
S21Matrix::~S21Matrix() { delete[] matrix_; }


// Присвоение матрице значений другой матрицы
S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  std::swap(matrix_, other.matrix_);
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  return *this;
}

// Оператор копирования
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    S21Matrix result(other);
    (*this) = std::move(result);
  }
  return *this;
}

// Индексация по элементам матрицы (строка, колонка)
double& S21Matrix::operator()(int rows, int cols) const {
  if (rows < 0 || cols < 0 || rows > rows_ || cols > cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[rows * cols_ + cols];
}

// Проверяет матрицы на равенство между собой
bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::abs((*this)(i, j) - other(i, j)) > EPS) {
        return false;
      }
    }
  }
  return true;
}

// Проверка на равенство матриц (EqMatrix)
bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

// Прибавляет вторую матрицу к текущей
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) += other(i, j);
    }
  }
}

// Сложение двух матриц
S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

// Вычитает из текущей матрицы другую
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) -= other(i, j);
    }
  }
}

// Вычитание одной матрицы из другой
S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

// Умножает текущую матрицу на число
void S21Matrix::MulNumber(double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) *= num;
    }
  }
}

// Умножение матрицы на число
S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

//Умножает текущую матрицу на вторую
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Incorrect input, error: A.columns != B.rows");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = std::move(result);
}

// Умножение матриц
S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

// Присвоение сложения (SumMatrix)
void S21Matrix::operator+=(const S21Matrix& other) { SumMatrix(other); }

// Присвоение разности (SubMatrix)
void S21Matrix::operator-=(const S21Matrix& other) { SubMatrix(other); }

// Присвоение умножения (MulMatrix)
void S21Matrix::operator*=(const S21Matrix& other) { MulMatrix(other); }

// Присвоение умножения (MulNumber)
void S21Matrix::operator*=(double num) { MulNumber(num); }

// Создание транспонированной матрицы из текущей (копия)
S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      result(i, j) = (*this)(j, i);
    }
  }
  return result;
}

// Получение количества строк
int S21Matrix::GetRows() const { return rows_; }

// Получение количества столбцов
int S21Matrix::GetCols() const { return cols_; }

// Установить количество строк
void S21Matrix::SetRows(int rows) {
  if (rows < 0) {
    throw std::invalid_argument(
        "Incorrect input, the number of rows cannot be negative");
  }
  if (rows != rows_) {
    S21Matrix result(rows, cols_);
    for (int i = 0; i < std::min(rows, rows_); ++i) {
      for (int j = 0; j < cols_; ++j) {
        result(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(result);
  }
}

// Установить количество столбцов
void S21Matrix::SetCols(int cols) {
  if (cols < 0) {
    throw std::invalid_argument(
        "Incorrect input, the number of columns cannot be negative");
  }
  if (cols != cols_) {
    S21Matrix result(rows_, cols);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < std::min(cols, cols_); ++j) {
        result(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(result);
  }
}

// Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее
S21Matrix S21Matrix::CalcComplements() const {
  if (cols_ != rows_) {
    throw std::invalid_argument("Incorrect input, error: columns != rows");
  }
  return MinorMatrix(rows_);
}

S21Matrix S21Matrix::MinorMatrix(int n) const {
  S21Matrix result(n, n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      S21Matrix M(n - 1, n - 1);
      int x = 0;
      for (int k = 0; k < n; ++k) {
        if (k == i) {
          continue;
        }
        int y = 0;
        for (int l = 0; l < n; ++l) {
          if (l == j) {
            continue;
          }
          M(x, y) = (*this)(k, l);
          y++;
        }
        x++;
      }
      int sign = ((i + j) % 2 == 0 ? 1 : -1);
      result(i, j) = sign * M.DetMinor(n - 1);
    }
  }
  return result;
}

// Вычисляет и возвращает определитель текущей матрицы
double S21Matrix::Determinant() const {
  if (cols_ != rows_) {
    throw std::invalid_argument("Incorrect input, error: columns != rows");
  }
  return DetMinor(rows_);
}

double S21Matrix::DetMinor(int n) const {
  if (n == 1) {
    return (*this)(0, 0);
  }
  double det = 0;
  S21Matrix M(n - 1, n - 1);
  for (int j = 0; j < n; ++j) {
    for (int i = 1; i < n; ++i) {
      for (int k = 0; k < j; ++k) {
        M(i - 1, k) = (*this)(i, k);
      }
      for (int k = j + 1; k < n; ++k) {
        M(i - 1, k - 1) = (*this)(i, k);
      }
    }
    double sign = (j % 2 == 0) ? 1 : -1;
    det += (*this)(0, j) * sign * M.DetMinor(n - 1);
  }
  return det;
}

// Вычисляет и возвращает обратную матрицу
S21Matrix S21Matrix::InverseMatrix() const {
  S21Matrix result(*this);
  double det = result.Determinant();
  if (rows_ != cols_ || std::abs(det) < EPS) {
    throw std::invalid_argument(
        "Incorrect input, error: columns != rows or determinant = 0");
  }
  result = result.CalcComplements().Transpose();
  result.MulNumber(rows_ == 1 ? std::pow(det, -2) : (1.0 / det));
  return result;
}

S21Matrix operator*(double num, const S21Matrix& other) {
  S21Matrix result(other);
  result.MulNumber(num);
  return result;
}
