#include "SmartCalc/calculator.h"
#include "SmartCalc/credit.h"
#include <check.h>

#define EPS 7
#define EPS_CREDIT 2

START_TEST(test_case_calc_1) {
  char *input_str = "1+2*3";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 7.0, EPS);
}
END_TEST

START_TEST(test_case_calc_2) {
  char *input_str = "1+2*3/4";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 1 + 2 * 3 / 4, EPS);
}
END_TEST

START_TEST(test_case_calc_3) {
  char *input_str = "1/3";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 1 / 3, EPS);
}
END_TEST

START_TEST(test_case_calc_4) {
  char *input_str = "(1.2+2.1)/3";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), (1.2 + 2.1) / 3, EPS);
}
END_TEST

START_TEST(test_case_calc_5) {
  char *input_str = "5.0mod3.0";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 2, EPS);
}
END_TEST

START_TEST(test_case_calc_6) {
  char *input_str = "---1";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), -1, EPS);
}
END_TEST

START_TEST(test_case_calc_7) {
  char *input_str = "-+-1";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 1, EPS);
}
END_TEST

START_TEST(test_case_calc_8) {
  char *input_str = "sin(0)";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 0, EPS);
}
END_TEST

START_TEST(test_case_calc_9) {
  char *input_str = "cos(0)";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 1, EPS);
}
END_TEST

START_TEST(test_case_calc_10) {
  char *input_str = "atan(tan(1))+asin(sin(1))+acos(cos(1))";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 3, EPS);
}
END_TEST

START_TEST(test_case_calc_11) {
  char *input_str = "6+4*3*5+2+7";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 74, EPS);
}
END_TEST

START_TEST(test_case_calc_12) {
  char *input_str = "(cos(1/3)*sin(1.352^9/(4+3))/76.56)*log(150)";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 0.0223863, EPS);
}
END_TEST

START_TEST(test_case_calc_13) {
  char *input_str = "acos0.5";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 1.0471976, EPS);
}
END_TEST

START_TEST(test_case_calc_14) {
  char *input_str = "sqrt(1)mod1";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 0, EPS);
}
END_TEST

START_TEST(test_case_calc_15) {
  char *input_str = "1-1mod1";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 1, EPS);
}
END_TEST

START_TEST(test_case_calc_16) {
  char *input_str = "asin(1)+ln(5)+log(5)";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 1.5707963, EPS);
}
END_TEST

START_TEST(test_case_calc_17) {
  char *input_str = "X+X";
  char result_str[200];
  double X = 3.5;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 1, EPS);
}
END_TEST

START_TEST(test_case_calc_18) {
  char *input_str = "asin(1)+ln(5)";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 3.1802342, EPS);
}
END_TEST

START_TEST(test_case_calc_19) {
  char *input_str = "atan(X";
  char result_str[200];
  double X = 5;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 0);
  ck_assert_double_eq_tol(strtod(result_str, NULL), 1.3734008, EPS);
}
END_TEST

START_TEST(test_case_calc_20) {
  char *input_str = "3+";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 1);
  ck_assert_pstr_eq(result_str, "INCORRECT EXPRESSION");
}
END_TEST

START_TEST(test_case_calc_21) {
  char *input_str = "l0";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 1);
  ck_assert_pstr_eq(result_str, "INCORRECT EXPRESSION");
}
END_TEST

START_TEST(test_case_calc_22) {
  char *input_str = "1.2.3";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 1);
  ck_assert_pstr_eq(result_str, "INCORRECT EXPRESSION");
}
END_TEST

START_TEST(test_case_calc_23) {
  char *input_str = "=";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 1);
  ck_assert_pstr_eq(result_str, "INCORRECT EXPRESSION");
}
END_TEST

START_TEST(test_case_calc_24) {
  char *input_str = ")";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 2);
  ck_assert_pstr_eq(result_str, "PARENTHESIS ERROR");
}
END_TEST

START_TEST(test_case_calc_25) {
  char *input_str = "1/0";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 3);
  ck_assert_pstr_eq(result_str, "CALCULATION ERROR");
}
END_TEST

START_TEST(test_case_calc_26) {
  char *input_str = "1mod0.1";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 3);
  ck_assert_pstr_eq(result_str, "CALCULATION ERROR");
}
END_TEST

START_TEST(test_case_calc_27) {
  char *input_str = "acos(5)";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 3);
  ck_assert_pstr_eq(result_str, "CALCULATION ERROR");
}
END_TEST

START_TEST(test_case_calc_28) {
  char *input_str = "asin(5)";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 3);
  ck_assert_pstr_eq(result_str, "CALCULATION ERROR");
}
END_TEST

START_TEST(test_case_calc_29) {
  char *input_str = "sqrt(-5)";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 3);
  ck_assert_pstr_eq(result_str, "CALCULATION ERROR");
}
END_TEST

START_TEST(test_case_calc_30) {
  char *input_str = "ln(-5)";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 3);
  ck_assert_pstr_eq(result_str, "CALCULATION ERROR");
}
END_TEST

START_TEST(test_case_calc_31) {
  char *input_str = "log(-5)";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 3);
  ck_assert_pstr_eq(result_str, "CALCULATION ERROR");
}
END_TEST

START_TEST(test_case_calc_32) {
  char *input_str = "log(sqrt(-5))";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 3);
  ck_assert_pstr_eq(result_str, "CALCULATION ERROR");
}
END_TEST

START_TEST(test_case_calc_33) {
  char *input_str = "10^600";
  char result_str[200];
  double X = 0;

  int res_code = calculate(input_str, result_str, X);
  ck_assert_int_eq(res_code, 4);
  ck_assert_pstr_eq(result_str, "inf");
}
END_TEST

START_TEST(test_case_credit_1) {
  double credit_sum = 20000;
  int credit_term = 36;
  float credit_percent = 12;
  int type = 0;
  char monthly_payment[256];
  char overpayment[256];
  char full_payment[256];
  credit(credit_sum, credit_term, credit_percent, type, monthly_payment,
         overpayment, full_payment);

  ck_assert_double_eq_tol(strtod(monthly_payment, NULL), 664.29, EPS_CREDIT);
  ck_assert_double_eq_tol(strtod(overpayment, NULL), 3914.30, EPS_CREDIT);
  ck_assert_double_eq_tol(strtod(full_payment, NULL), 23914.30, EPS_CREDIT);
}
END_TEST

START_TEST(test_case_credit_2) {
  double credit_sum = 20000;
  int credit_term = 36;
  float credit_percent = 12;
  int type = 1;
  char monthly_payment[256];
  char overpayment[256];
  char full_payment[256];
  credit(credit_sum, credit_term, credit_percent, type, monthly_payment,
         overpayment, full_payment);

  ck_assert_pstr_eq(monthly_payment, "755.56 ... 561.11");
  ck_assert_double_eq_tol(strtod(overpayment, NULL), 3700.00, EPS_CREDIT);
  ck_assert_double_eq_tol(strtod(full_payment, NULL), 23700.00, EPS_CREDIT);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("SmartCalc: ");
  TCase *tc_calc = tcase_create("calculator: ");
  TCase *tc_credit = tcase_create("credit: ");
  SRunner *sr = srunner_create(s1);
  int result;

  suite_add_tcase(s1, tc_calc);
  suite_add_tcase(s1, tc_credit);

  tcase_add_test(tc_calc, test_case_calc_1);
  tcase_add_test(tc_calc, test_case_calc_2);
  tcase_add_test(tc_calc, test_case_calc_3);
  tcase_add_test(tc_calc, test_case_calc_4);
  tcase_add_test(tc_calc, test_case_calc_5);
  tcase_add_test(tc_calc, test_case_calc_6);
  tcase_add_test(tc_calc, test_case_calc_7);
  tcase_add_test(tc_calc, test_case_calc_8);
  tcase_add_test(tc_calc, test_case_calc_9);
  tcase_add_test(tc_calc, test_case_calc_10);
  tcase_add_test(tc_calc, test_case_calc_11);
  tcase_add_test(tc_calc, test_case_calc_12);
  tcase_add_test(tc_calc, test_case_calc_13);
  tcase_add_test(tc_calc, test_case_calc_14);
  tcase_add_test(tc_calc, test_case_calc_15);
  tcase_add_test(tc_calc, test_case_calc_16);
  tcase_add_test(tc_calc, test_case_calc_17);
  tcase_add_test(tc_calc, test_case_calc_18);
  tcase_add_test(tc_calc, test_case_calc_19);
  tcase_add_test(tc_calc, test_case_calc_20);
  tcase_add_test(tc_calc, test_case_calc_21);
  tcase_add_test(tc_calc, test_case_calc_22);
  tcase_add_test(tc_calc, test_case_calc_23);
  tcase_add_test(tc_calc, test_case_calc_24);
  tcase_add_test(tc_calc, test_case_calc_25);
  tcase_add_test(tc_calc, test_case_calc_26);
  tcase_add_test(tc_calc, test_case_calc_27);
  tcase_add_test(tc_calc, test_case_calc_28);
  tcase_add_test(tc_calc, test_case_calc_29);
  tcase_add_test(tc_calc, test_case_calc_30);
  tcase_add_test(tc_calc, test_case_calc_31);
  tcase_add_test(tc_calc, test_case_calc_32);
  tcase_add_test(tc_calc, test_case_calc_33);

  tcase_add_test(tc_credit, test_case_credit_1);
  tcase_add_test(tc_credit, test_case_credit_2);

  srunner_run_all(sr, CK_ENV);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result == 0 ? 0 : 1;
}
