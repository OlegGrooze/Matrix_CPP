#include <gtest/gtest.h>

#include "s21_matrix_oop.h"
#include "tests.h"

namespace {

TEST_F(MatrixTest, test_sum) {
  S21Matrix result(3, 3);
  S21Matrix tmp1 = mx1, tmp2 = mx1, tmp3;
  result(0, 0) = 26677.003804244;
  result(0, 1) = 51238.008118;
  result(0, 2) = 121659;
  result(1, 0) = -629912.12398412;
  result(1, 1) = 313403.07001178;
  result(1, 2) = 10569.85;
  result(2, 0) = 563703;
  result(2, 1) = -298086.09921;
  result(2, 2) = -31256.87231111;

  tmp1.SumMatrix(mx2);
  tmp2 += mx2;
  tmp3 = mx1 + mx2;
  ASSERT_NO_THROW(mx1.SumMatrix(mx2));
  EXPECT_TRUE(result == tmp1 && result == tmp2 && result == tmp3);
  EXPECT_NE(mx2 == result, true);
}

TEST_F(MatrixTest, test_sub) {
  S21Matrix result{3, 3};
  S21Matrix tmp1 = mx1, tmp2 = mx1, tmp3;
  result(0, 0) = -17292.619038244;
  result(0, 1) = -51249.991882;
  result(0, 2) = 121035;
  result(1, 0) = -629924.12398412;
  result(1, 1) = 313478.92998822;
  result(1, 2) = 10561.85;
  result(2, 0) = -461181;
  result(2, 1) = -298081.90079;
  result(2, 2) = -31250.87231111;

  tmp1.SubMatrix(mx2);
  tmp2 -= mx2;
  tmp3 = mx1 - mx2;
  EXPECT_TRUE(result == tmp1 && result == tmp2 && result == tmp3);
}

TEST_F(MatrixTest, test_mulnum) {
  S21Matrix result{3, 3};
  S21Matrix tmp1 = mx2, tmp2 = mx2, tmp3, tmp4;
  double num = 21.129821;

  result(0, 0) = 464535.130050;
  result(0, 1) = 1082776.547324;
  result(0, 2) = 6592.504152;
  result(1, 0) = 126.778926;
  result(1, 1) = -801.453862;
  result(1, 2) = 84.519284;
  result(2, 0) = 10827807.732882;
  result(2, 1) = -44.355932;
  result(2, 2) = -63.389463;

  tmp1.MulNumber(num);
  tmp2 *= num;
  tmp3 = mx2 * num;
  tmp4 = num * mx2;
  EXPECT_TRUE(result == tmp1 && result == tmp2 && result == tmp3
             && result == tmp4);
}

TEST_F(MatrixTest, test_mul) {
  S21Matrix result{3, 3};
  S21Matrix tmp1 = mx1, tmp2 = mx1, tmp3;
  result(0, 0) = 62286456302.741160;
  result(0, 1) = 240192200.910595;
  result(0, 2) = 1099899.055968;
  result(1, 0) = -8432365214.914675;
  result(1, 1) = -32291435338.817888;
  result(1, 2) = -195312388.233045;
  result(2, 0) = -14890621920.585441;
  result(2, 1) = 2638190615.049864;
  result(2, 2) = 14894857.616933;

  tmp1.MulMatrix(mx2);
  tmp2 *= mx2;
  tmp3 = mx1 * mx2;
  EXPECT_TRUE(result == tmp1 && result == tmp2 && result == tmp3);
}

TEST_F(MatrixTest, test_get) {
  S21Matrix tmp = mx2, tmp1 = std::move(mx2);
  EXPECT_EQ(tmp.GetCols(), 3);
  EXPECT_EQ(tmp.GetRows(), 3);
  EXPECT_EQ(tmp1.GetCols(), 3);
  EXPECT_EQ(tmp1.GetRows(), 3);
  EXPECT_NEAR(tmp(0, 0), 21984.811421244, 1e-7);
  EXPECT_NEAR(tmp1(0, 0), 21984.811421244, 1e-7);

  S21Matrix tmp2(mx1), tmp3(std::move(mx1)), tmp4;

  EXPECT_EQ(tmp2.GetCols(), 3);
  EXPECT_EQ(tmp2.GetRows(), 3);
  EXPECT_EQ(tmp3.GetCols(), 3);
  EXPECT_EQ(tmp3.GetRows(), 3);
  EXPECT_EQ(tmp4.GetRows(), 1);
  EXPECT_EQ(tmp4.GetRows(), 1);

  EXPECT_NEAR(tmp2(2, 2), -31253.87231111, 1e-7);
  EXPECT_NEAR(tmp3(2, 2), -31253.87231111, 1e-7);
  EXPECT_EQ(tmp4(0, 0), 0);
}

TEST_F(MatrixTest, test_error) {
  EXPECT_THROW(S21Matrix tmp(-1, 2), std::exception);
  EXPECT_THROW(S21Matrix tmp(1, -2), std::exception);
}

TEST_F(MatrixTest, test_set) {
  mx1.SetRows(2);
  mx2.SetCols(4);
  EXPECT_EQ(mx1.GetRows(), 2);
  EXPECT_TRUE(mx2.GetCols() == 4 && mx2(2, 3) == 0);
  mx1.SetRows(2);
  mx2.SetCols(4);
  EXPECT_EQ(mx1.GetRows(), 2);
  EXPECT_EQ(mx2.GetCols(), 4);
}

TEST_F(MatrixTest, test_error_set) {
  EXPECT_THROW(mx1.SetRows(0), std::invalid_argument);
  EXPECT_THROW(mx2.SetCols(-1), std::invalid_argument);
}

TEST_F(MatrixTest, test_eq) {
  S21Matrix tmp(mx1);
  EXPECT_TRUE(mx1 == tmp);
  EXPECT_FALSE(mx1 == mx2);
  tmp.SetCols(4);
  EXPECT_FALSE(mx1 == tmp);
  tmp.SetCols(3);
  tmp.SetRows(4);
  EXPECT_FALSE(mx1 == tmp);
}

TEST_F(MatrixTest, test_determinant) {
  double det1 = mx1.Determinant(), det2 = mx2.Determinant();

  EXPECT_NEAR(det1, 20804354296571035.477, 10);
  EXPECT_NEAR(det2, 111106234843.44866534, 1e-4);
}

TEST_F(MatrixTest, test_transpose) {
  S21Matrix result(4, 3);
  result(0, 0) = 4692.192383;
  result(0, 1) = -629918.123984;
  result(0, 2) = 51261;
  result(1, 0) = -5.991882;
  result(1, 1) = 313441;
  result(1, 2) = -298084;
  result(2, 0) = 121347;
  result(2, 1) = 10565.85;
  result(2, 2) = -31253.872312;
  result(3, 0) = 0;
  result(3, 1) = 0;
  result(3, 2) = 0;

  mx1.SetCols(4);
  EXPECT_TRUE(mx1.Transpose() == result);
}

TEST_F(MatrixTest, test_complement) {
  S21Matrix result(3, 3);
  result(0, 0) = 122.186804;
  result(0, 1) = 2049786;
  result(0, 2) = 19436906.428173;
  result(1, 0) = 153077.04648;
  result(1, 1) = -159947858.434264;
  result(1, 2) = 26259623998.735985;
  result(2, 0) = 216810.156324;
  result(2, 1) = -86067.245684;
  result(2, 2) = -1141347.638226;
  EXPECT_TRUE(mx2.CalcComplements() == result);
}

TEST_F(MatrixTest, test_inverse) {
  S21Matrix result(3, 3);
  result(0, 0) = 0;
  result(0, 1) = -0.000002;
  result(0, 2) = -0.000002;
  result(1, 0) = -0.000001;
  result(1, 1) = 0;
  result(1, 2) = -0.000004;
  result(2, 0) = 0.000008;
  result(2, 1) = 0;
  result(2, 2) = 0;

  EXPECT_TRUE(mx1.InverseMatrix() == result);
}

TEST_F(MatrixTest, test_error_square) {
  mx1.SetRows(2);
  EXPECT_THROW((void)mx1.Determinant(), std::invalid_argument);
  EXPECT_THROW(mx1.CalcComplements(), std::invalid_argument);
  EXPECT_THROW(mx1.InverseMatrix(), std::invalid_argument);
}

TEST_F(MatrixTest, test_error_inverse) {
  S21Matrix tmp(2, 2);
  tmp(0, 0) = 1;
  tmp(0, 1) = 1;
  tmp(1, 0) = 1;
  tmp(1, 1) = 1;

  EXPECT_THROW(tmp.InverseMatrix(), std::invalid_argument);
}

TEST_F(MatrixTest, test_error_index) {
  EXPECT_THROW(mx1(10, 2), std::out_of_range);
  EXPECT_THROW(mx1(1, 20), std::out_of_range);
  EXPECT_THROW(mx1(-1, 2), std::out_of_range);
  EXPECT_THROW(mx1(1, -2), std::out_of_range);
}

}  // namespace

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
