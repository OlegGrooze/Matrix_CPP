#ifndef CPP1_S21_MATRIXPLUS_1_SRC_TESTS_H
#define CPP1_S21_MATRIXPLUS_1_SRC_TESTS_H

#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

class MatrixTest : public ::testing::Test {
  void SetUp() override {
    mx1 = S21Matrix(3, 3);
    mx1(0, 0) = 4692.192383;
    mx1(0, 1) = -5.991882;
    mx1(0, 2) = 121347;
    mx1(1, 0) = -629918.12398412;
    mx1(1, 1) = 313441;
    mx1(1, 2) = 10565.85;
    mx1(2, 0) = 51261;
    mx1(2, 1) = -298084;
    mx1(2, 2) = -31253.87231111;

    mx2 = S21Matrix(3, 3);
    mx2(0, 0) = 21984.811421244;
    mx2(0, 1) = 51244;
    mx2(0, 2) = 312;
    mx2(1, 0) = 6;
    mx2(1, 1) = -37.92998822;
    mx2(1, 2) = 4;
    mx2(2, 0) = 512442;
    mx2(2, 1) = -2.09921;
    mx2(2, 2) = -3;
  }
  void TearDown() override {}

 protected:
  S21Matrix mx1, mx2;
};

#endif  // CPP1_S21_MATRIXPLUS_1_SRC_TESTS_H
