#ifndef CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H

#define EPS 10E-6

#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

class S21Matrix {
 public:
  S21Matrix();  // Конструктор по умолчанию
  S21Matrix(int rows, int cols);  // Параметризованный конструктор
  S21Matrix(const S21Matrix& other);  // Конструктор копирования
  S21Matrix(S21Matrix&& other);  // Конструктор передачи
  ~S21Matrix();  // Деструктор

  bool EqMatrix(const S21Matrix& other) const;  // Сравнение матриц
  void SumMatrix(const S21Matrix& other);  // Суммирование матриц
  void SubMatrix(const S21Matrix& other);  // Вычитание из текущей матрицы другой
  void MulNumber(double num);  // Умножение матрицы на число
  void MulMatrix(const S21Matrix& other);  // Умножение матрицы на другую матрицу
  S21Matrix Transpose() const;  // Создание транспонированной матрицы из текущей (копия)
  S21Matrix CalcComplements() const;  // Вычисление и возврат матрицы алгебраических дополнений
  double Determinant() const;  // Детерминанта текущей матрицы
  double DetMinor(int) const;  // ДетМинор текущей матрицы
  S21Matrix InverseMatrix() const;  // Инверсия текущей матрицы
  S21Matrix MinorMatrix(int) const;  // Минор текущей матрицы

  bool operator==(const S21Matrix&) const;  // Проверка равенства матриц
  S21Matrix operator+(const S21Matrix&) const;  // Сложение матриц
  S21Matrix operator-(const S21Matrix&) const;  // Разность матриц
  S21Matrix operator*(const S21Matrix&) const;  // Умножение матриц
  S21Matrix operator*(double) const;  //  Умножение матрицы на число
  S21Matrix &operator=(S21Matrix&&);  // Присвоение матрице значений другой матрицы
  S21Matrix &operator=(const S21Matrix& other); // Оператор копирования

  void operator+=(const S21Matrix&);  // Присвоение сложения (SumMatrix)
  void operator-=(const S21Matrix&);  // Присвоение разности (SubMatrix)
  void operator*=(const S21Matrix&);  // Присвоение умножения (MulMatrix)
  void operator*=(double);  // Присвоение умножения на число (MulNumber)
  double &operator()(int rows, int cols) const;  // Индексация элементов матрицы

  int GetRows() const;  // геттер строк
  int GetCols() const;  // геттер столбцов
  void SetRows(int rows);  // сеттер строк
  void SetCols(int cols);  // сеттер столбцов

 private:
  int rows_, cols_;  // Строки и столбцы
  double *matrix_;   // Указатель на память, занятую матрицей
};

S21Matrix operator*(double, const S21Matrix&);  // Умножение числа на матрицу

#endif  // CPP1_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H
