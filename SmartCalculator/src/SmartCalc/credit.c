#include "credit.h"

void credit(double credit_sum, int month, double percent, int type,
            char *month_pay, char *overpayment, char *full_payment) {
  if (type == 0) { // annuity
    double month_percent = percent / (12.0 * 100.0);
    double koeff = (month_percent * pow(1 + month_percent, month)) /
                   (pow(1 + month_percent, month) - 1);
    double month_pay_double = credit_sum * koeff;
    double full_payment_double = month_pay_double * month;
    double overpayment_double = full_payment_double - credit_sum;

    sprintf(month_pay, "%.2lf", month_pay_double);
    sprintf(overpayment, "%.2lf", overpayment_double);
    sprintf(full_payment, "%.2lf", full_payment_double);
  } else if (type == 1) { // differentiated
    double month_pay_double_min = 0, month_pay_double_max = 0;
    double month_credit_sum = credit_sum / month;
    double full_payment_double = 0;

    for (int i = 1; i <= month; i++) {
      double Sn = credit_sum - ((i - 1) * month_credit_sum);
      double month_percent = Sn * (percent / (12.0 * 100.0));
      double month_pay = month_credit_sum + month_percent;

      if (i == 1) {
        month_pay_double_max = month_pay;
      } else if (i == month) {
        month_pay_double_min = month_pay;
      }
      full_payment_double += month_pay;
    }
    double overpayment_double = full_payment_double - credit_sum;
    sprintf(month_pay, "%.2lf ... %.2lf", month_pay_double_max,
            month_pay_double_min);
    sprintf(overpayment, "%.2lf", overpayment_double);
    sprintf(full_payment, "%.2lf", full_payment_double);
  }
}
