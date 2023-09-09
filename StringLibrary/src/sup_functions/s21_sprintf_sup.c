#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

void my_itoa2(long num, char *str) {
  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
  } else {
    int counter = 0;
    long long dec = 1;
    while (dec < num) {
      dec *= 10;
    }
    if (dec != num) {
      dec /= 10;
    }
    while (dec != 0) {
      str[counter] = '0' + num / dec;
      counter++;
      num %= dec;
      dec /= 10;
    }
    str[counter] = '\0';
  }
}

char *my_ecvt(double sup, int n, int *decpnt, int *sign) {
  *sign = 0;

  if (sup < 0) {
    sup = -sup;
    *sign = 1;
  }

  *decpnt = 0;
  char *ans = (char *)malloc(100 * sizeof(char));

  if (sup == 0.0) {
    *decpnt = 1;

    for (int i = 0; i < n; ++i) {
      ans[i] = '0';
    }
    ans[n] = '\0';
  } else {
    double s = sup;
    if (s >= 1) {
      while (s >= 1) {
        (*decpnt)++;
        s /= 10;
      }
    } else {
      s *= 10;

      while (s < 1) {
        (*decpnt)--;
        s *= 10;
      }
    }

    n = n - *decpnt;

    for (int i = 0; i < n; ++i) {
      sup *= 10;
    }
    sup = round(sup);

    long cur = (long)sup;

    my_itoa2(cur, ans);
  }

  return ans;
}

char *my_fcvt(double sup, int n, int *decpnt, int *sign) {
  *sign = 0;

  if (sup < 0) {
    sup = -sup;
    *sign = 1;
  }

  *decpnt = 0;
  char *ans = (char *)malloc(100 * sizeof(char));

  if (sup == 0.0) {
    for (int i = 0; i < n; ++i) {
      ans[i] = '0';
    }
    ans[n] = '\0';
  } else {
    double s = sup;
    if (s >= 1) {
      while (s >= 1) {
        (*decpnt)++;
        s /= 10;
      }
    } else {
      s *= 10;

      while (s < 1) {
        (*decpnt)--;
        s *= 10;
      }

      if (*decpnt < -n) {
        *decpnt = -n;
      }
    }

    for (int i = 0; i < n; ++i) {
      sup *= 10;
    }
    sup = round(sup);

    long cur = (long)sup;

    my_itoa2(cur, ans);

    if (ans[0] == '0') {
      ans[0] = '\0';
    }
  }

  return ans;
}

void my_itoa(long num, char *str, fl cases) {
  if (num == 0 && !cases.a_fl) {
    str[0] = '0';
    str[1] = '\0';
  } else {
    int counter = 0, sym_count = 1;
    if (num < 0) {
      str[counter] = '-';
      counter++;
      num = -num;
    } else if (cases.p_fl) {
      str[counter] = '+';
      counter++;
    } else if (cases.s_fl) {
      str[counter] = ' ';
      counter++;
    }
    long long dec = 1;
    while (dec < num) {
      sym_count++;
      dec *= 10;
    }
    if (dec != num) {
      dec /= 10;
      sym_count--;
    }
    if (cases.a_fl && num == 0 && cases.acc == 0) {
      str[0] = '\0';
    } else {
      if (cases.a_fl && sym_count < cases.acc) {
        for (int i = 0; i < cases.acc - sym_count; ++i) {
          str[counter] = '0';
          counter++;
        }
      }
      while (dec != 0) {
        str[counter] = '0' + num / dec;
        counter++;
        num %= dec;
        dec /= 10;
      }
      str[counter] = '\0';
    }
  }
}

void my_otoa(long unsigned num, char *str, fl cases) {
  int counter = 0, sym_count = 1;

  if (num != 0 && cases.r_fl) {
    str[counter] = '0';
    ++counter;
  }

  unsigned long long dec = 1;

  while (dec < num) {
    dec *= 8;
    sym_count++;
  }

  if (dec != num) {
    dec /= 8;
    sym_count--;
  }

  if (cases.a_fl && num == 0 && cases.acc == 0) {
    str[0] = '\0';
  } else {
    if (cases.a_fl && sym_count < cases.acc) {
      for (int i = 0; i < cases.acc - sym_count; ++i) {
        str[counter] = '0';
        counter++;
      }
    }

    if (dec == 0) {
      str[counter] = '0';
      ++counter;
    }

    while (dec != 0) {
      int sup = num / dec;

      str[counter] = '0' + sup;

      counter++;
      num %= dec;
      dec /= 8;
    }

    str[counter] = '\0';
  }
}

void my_xtoa(long unsigned num, char *str, fl cases, int is_p) {
  int counter = 0, sym_count = 1;

  if ((num != 0 || is_p) && cases.r_fl) {
    str[counter] = '0';
    ++counter;
    str[counter] = 'x';
    ++counter;
  }

  unsigned long long dec = 1;

  while (dec < num) {
    dec *= 16;
    sym_count++;
  }

  if (dec != num) {
    dec /= 16;
    sym_count--;
  }

  if (cases.a_fl && num == 0 && cases.acc == 0) {
    str[0] = '\0';
  } else {
    if (cases.a_fl && sym_count < cases.acc) {
      for (int i = 0; i < cases.acc - sym_count; ++i) {
        str[counter] = '0';
        counter++;
      }
    }

    if (dec == 0) {
      str[counter] = '0';
      ++counter;
    }

    while (dec != 0) {
      int sup = num / dec;

      if (sup >= 10) {
        str[counter] = 'a' + sup - 10;
      } else {
        str[counter] = '0' + sup;
      }
      counter++;
      num %= dec;
      dec /= 16;
    }

    str[counter] = '\0';
  }
}

void my_Xtoa(long unsigned num, char *str, fl cases) {
  int counter = 0, sym_count = 1;

  if (num != 0 && cases.r_fl) {
    str[counter] = '0';
    ++counter;
    str[counter] = 'X';
    ++counter;
  }

  unsigned long long dec = 1;

  while (dec < num) {
    dec *= 16;
    sym_count++;
  }

  if (dec != num) {
    dec /= 16;
    sym_count--;
  }

  if (cases.a_fl && num == 0 && cases.acc == 0) {
    str[0] = '\0';
  } else {
    if (cases.a_fl && sym_count < cases.acc) {
      for (int i = 0; i < cases.acc - sym_count; ++i) {
        str[counter] = '0';
        counter++;
      }
    }

    if (dec == 0) {
      str[counter] = '0';
      ++counter;
    }

    while (dec != 0) {
      int sup = num / dec;

      if (sup >= 10) {
        str[counter] = 'A' + sup - 10;
      } else {
        str[counter] = '0' + sup;
      }
      counter++;
      num %= dec;
      dec /= 16;
    }

    str[counter] = '\0';
  }
}

void my_utoa(long unsigned num, char *str, fl cases) {
  int sym_count = 1;

  unsigned long long dec = 1;

  while (dec < num) {
    dec *= 10;
    sym_count++;
  }

  if (dec != num) {
    dec /= 10;
    sym_count--;
  }

  if (cases.a_fl && num == 0 && cases.acc == 0) {
    str[0] = '\0';
  } else {
    int counter = 0;
    if (cases.a_fl && sym_count < cases.acc) {
      for (int i = 0; i < cases.acc - sym_count; ++i) {
        str[counter] = '0';
        counter++;
      }
    }

    if (dec == 0) {
      str[counter] = '0';
      ++counter;
    }

    while (dec != 0) {
      str[counter] = '0' + num / dec;
      counter++;
      num %= dec;
      dec /= 10;
    }

    str[counter] = '\0';
  }
}
