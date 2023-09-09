#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

void f_case_sup2(long double sup, char *s, fl cases, int *decpnt, int *sign,
                 int *s_c) {
  char *out = my_fcvt(sup, cases.acc, decpnt, sign);
  if (sup >= 0 && cases.p_fl) {
    s[*s_c] = '+';
    (*s_c)++;
  } else if (sup >= 0 && cases.s_fl) {
    s[*s_c] = ' ';
    (*s_c)++;
  } else if (*sign) {
    s[*s_c] = '-';
    (*s_c)++;
  }
  int o_c = 0;
  for (int i = 0; i < (*decpnt); ++i) {
    s[*s_c] = out[o_c];
    (*s_c)++;
    o_c++;
  }
  if (*decpnt <= 0) {
    s[*s_c] = '0';
    (*s_c)++;
  }
  if (cases.acc > 0) {
    s[*s_c] = '.';
    (*s_c)++;
    int i = 0;
    for (; i < -(*decpnt); ++i) {
      s[*s_c] = '0';
      (*s_c)++;
    }
    for (; out[o_c] != '\0'; ++i) {
      s[*s_c] = out[o_c];
      (*s_c)++;
      o_c++;
    }
  }
  if (out != NULL) {
    free(out);
  }
  s[*s_c] = '\0';
}

void f_case_sup(long double sup, char *s, fl cases) {
  int decpnt, sign;
  int s_c = 0;

  if (cases.acc != 0) {
    f_case_sup2(sup, s, cases, &decpnt, &sign, &s_c);
  } else {
    long long cur = (long long)roundf(sup);
    if (cur == 0) {
      if (cases.p_fl && sup >= 0) {
        s[s_c] = '+';
        s_c++;
      } else if (cases.s_fl && sup >= 0) {
        s[s_c] = ' ';
        s_c++;
      } else if (sup < 0) {
        s[s_c] = '-';
        s_c++;
      }
      s[s_c] = '0';
      s_c++;

    } else {
      my_itoa(cur, s, cases);
    }
    if (cases.r_fl) {
      int cur_c = 0;
      while (s[cur_c] != '\0') {
        cur_c++;
      }
      s[cur_c] = '.';
      s[cur_c + 1] = '\0';
    }
  }
}

void f_case(char *s, fl cases, va_list *fact) {
  if (cases.L_len == 0) {
    double sup = va_arg(*fact, double);
    f_case_sup(sup, s, cases);
  } else {
    long double sup = va_arg(*fact, long double);
    f_case_sup(sup, s, cases);
  }
}

void e_case(char *s, fl cases, va_list *fact, const char *format, int counter) {
  int decpnt, sign;
  char *out;
  if (cases.L_len) {
    long double sup = (long double)va_arg(*fact, long double);
    out = my_ecvt(sup, cases.acc + 1, &decpnt, &sign);
  } else {
    double sup = (double)va_arg(*fact, double);
    out = my_ecvt(sup, cases.acc + 1, &decpnt, &sign);
  }
  int s_c = 0;
  if (cases.p_fl && !sign) {
    s[s_c] = '+';
    s_c++;
  } else if (cases.s_fl && !sign) {
    s[s_c] = ' ';
    s_c++;
  } else if (sign) {
    s[s_c] = '-';
    s_c++;
  }
  int o_c = 0;
  s[s_c] = out[o_c];
  s_c++;
  o_c++;
  s[s_c] = '.';
  s_c++;
  while (out[o_c] != '\0') {
    s[s_c] = out[o_c];
    s_c++;
    o_c++;
  }
  if (format[counter] == 'e') {
    s[s_c] = 'e';
  } else {
    s[s_c] = 'E';
  }
  s_c++;
  decpnt -= 1;
  if (decpnt < 0) {
    s[s_c] = '-';
    decpnt = -decpnt;
  } else {
    s[s_c] = '+';
  }

  s_c++;
  s[s_c] = '0' + decpnt / 10;
  s_c++;
  s[s_c] = '0' + decpnt % 10;
  s_c++;
  s[s_c] = '\0';

  if (out != NULL) {
    free(out);
  }
}

void g_case(char *s, fl cases, va_list *fact) {
  if (cases.L_len) {
    long double sup = (long double)va_arg(*fact, long double);

    if (cases.p_fl && sup >= 0) {
      s[0] = '+';
      s++;
    } else if (cases.s_fl && sup >= 0) {
      s[0] = ' ';
      s++;
    }

    int d, sign;

    char *out = my_ecvt(sup, cases.acc, &d, &sign);

    if (out != NULL) {
      free(out);
    }

    if (d > cases.acc || d < 0) {
      int decpnt, sign;
      char *out;
      out = my_ecvt(sup, cases.acc + 1, &decpnt, &sign);

      int s_c = 0;
      if (cases.p_fl && !sign) {
        s[s_c] = '+';
        s_c++;
      } else if (cases.s_fl && !sign) {
        s[s_c] = ' ';
        s_c++;
      } else if (sign) {
        s[s_c] = '-';
        s_c++;
      }
      int o_c = 0;
      s[s_c] = out[o_c];
      s_c++;
      o_c++;
      int o_sup = o_c;

      while (out[o_sup] != '\0') {
        o_sup++;
      }
      o_sup--;
      while (o_sup > 0 && out[o_sup] == '0') {
        out[o_sup] = '\0';
        o_sup--;
      }
      if (out[o_c] != '\0') {
        s[s_c] = '.';
        s_c++;
      } else {
        s[s_c] = '\0';
      }

      while (out[o_c] != '\0') {
        s[s_c] = out[o_c];
        s_c++;
        o_c++;
      }

      s[s_c] = 'e';

      s_c++;
      decpnt -= 1;
      if (decpnt < 0) {
        s[s_c] = '-';
        decpnt = -decpnt;
      } else {
        s[s_c] = '+';
      }

      s_c++;
      s[s_c] = '0' + decpnt / 10;
      s_c++;
      s[s_c] = '0' + decpnt % 10;
      s_c++;
      s[s_c] = '\0';

      if (out != NULL) {
        free(out);
      }
    } else {
      cases.acc -= d;
      f_case_sup(sup, s, cases);
      cases.acc += d;

      int cnt = 0;
      int fl = 0;

      while (s[cnt] != '\0') {
        if (s[cnt] == '.') {
          fl = 1;
        }
        cnt++;
      }

      if (fl) {
        cnt--;
        while (cnt > 0 && s[cnt] == '0') {
          s[cnt] = '\0';
          cnt--;
        }
        if (s[cnt] == '.') {
          s[cnt] = '\0';
        }
      }
    }
  } else {
    double sup = (double)va_arg(*fact, double);

    if (cases.p_fl && sup >= 0) {
      s[0] = '+';
      s++;
    } else if (cases.s_fl && sup >= 0) {
      s[0] = ' ';
      s++;
    }

    int d, sign;

    char *out = my_ecvt(sup, cases.acc, &d, &sign);

    if (out != NULL) {
      free(out);
    }

    if (d > cases.acc || d < 0) {
      int decpnt, sign;
      char *out;
      out = my_ecvt(sup, cases.acc + 1, &decpnt, &sign);

      int s_c = 0;
      if (cases.p_fl && !sign) {
        s[s_c] = '+';
        s_c++;
      } else if (cases.s_fl && !sign) {
        s[s_c] = ' ';
        s_c++;
      } else if (sign) {
        s[s_c] = '-';
        s_c++;
      }
      int o_c = 0;
      s[s_c] = out[o_c];
      s_c++;
      o_c++;
      int o_sup = o_c;

      while (out[o_sup] != '\0') {
        o_sup++;
      }
      o_sup--;
      while (o_sup > 0 && out[o_sup] == '0') {
        out[o_sup] = '\0';
        o_sup--;
      }
      if (out[o_c] != '\0') {
        s[s_c] = '.';
        s_c++;
      } else {
        s[s_c] = '\0';
      }

      while (out[o_c] != '\0') {
        s[s_c] = out[o_c];
        s_c++;
        o_c++;
      }

      s[s_c] = 'e';

      s_c++;
      decpnt -= 1;
      if (decpnt < 0) {
        s[s_c] = '-';
        decpnt = -decpnt;
      } else {
        s[s_c] = '+';
      }

      s_c++;
      s[s_c] = '0' + decpnt / 10;
      s_c++;
      s[s_c] = '0' + decpnt % 10;
      s_c++;
      s[s_c] = '\0';

      if (out != NULL) {
        free(out);
      }
    } else {
      cases.acc -= d;
      f_case_sup(sup, s, cases);
      cases.acc += d;

      int cnt = 0;
      int fl = 0;

      while (s[cnt] != '\0') {
        if (s[cnt] == '.') {
          fl = 1;
        }
        cnt++;
      }

      if (fl) {
        cnt--;
        while (cnt > 0 && s[cnt] == '0') {
          s[cnt] = '\0';
          cnt--;
        }
        if (s[cnt] == '.') {
          s[cnt] = '\0';
        }
      }
    }
  }
}

void d_case(char *s, fl cases, va_list *fact) {
  if (cases.h_len) {
    short sup = (short)va_arg(*fact, int);
    my_itoa(sup, s, cases);
  } else if (cases.l_len) {
    long sup = (long)va_arg(*fact, long);
    my_itoa(sup, s, cases);
  } else {
    int sup = va_arg(*fact, int);
    my_itoa(sup, s, cases);
  }
}

void u_case(char *s, fl cases, va_list *fact) {
  if (cases.h_len) {
    unsigned short sup = (unsigned short)va_arg(*fact, unsigned int);
    my_utoa(sup, s, cases);
  } else if (cases.l_len) {
    unsigned long sup = (unsigned long)va_arg(*fact, long);
    my_utoa(sup, s, cases);
  } else {
    unsigned sup = va_arg(*fact, unsigned int);
    my_utoa(sup, s, cases);
  }
}

void s_case(char *s, fl cases, va_list *fact) {
  char *sup_s = va_arg(*fact, char *);
  int s_counter = 0;
  while (sup_s[s_counter] != '\0' && ((!cases.a_fl) || cases.acc > s_counter)) {
    s[s_counter] = sup_s[s_counter];
    s_counter++;
  }
  s[s_counter] = '\0';
}

void x_case(char *s, fl cases, va_list *fact) {
  if (cases.h_len) {
    unsigned short sup = (unsigned short)va_arg(*fact, unsigned int);
    my_xtoa(sup, s, cases, 0);
  } else if (cases.l_len) {
    unsigned long sup = (unsigned long)va_arg(*fact, long);
    my_xtoa(sup, s, cases, 0);
  } else {
    unsigned sup = va_arg(*fact, unsigned int);
    my_xtoa(sup, s, cases, 0);
  }
}

void X_case(char *s, fl cases, va_list *fact) {
  if (cases.h_len) {
    unsigned short sup = (unsigned short)va_arg(*fact, unsigned int);
    my_Xtoa(sup, s, cases);
  } else if (cases.l_len) {
    unsigned long sup = (unsigned long)va_arg(*fact, long);
    my_Xtoa(sup, s, cases);
  } else {
    unsigned sup = va_arg(*fact, unsigned int);
    my_Xtoa(sup, s, cases);
  }
}

void o_case(char *s, fl cases, va_list *fact) {
  if (cases.h_len) {
    unsigned short sup = (unsigned short)va_arg(*fact, unsigned int);
    my_otoa(sup, s, cases);
  } else if (cases.l_len) {
    unsigned long sup = (unsigned long)va_arg(*fact, long);
    my_otoa(sup, s, cases);
  } else {
    unsigned sup = va_arg(*fact, unsigned int);
    my_otoa(sup, s, cases);
  }
}

void p_case(char *s, fl cases, va_list *fact) {
  cases.r_fl = 1;

  unsigned long sup = (unsigned long)va_arg(*fact, long);
  my_xtoa(sup, s, cases, 1);
}

void str_forming(const char *format, char *s, fl cases, int counter,
                 va_list *fact, const int cur_it) {
  for (int i = 0; i < 100; ++i) {
    s[i] = '\0';
  }
  if (format[counter] == '%') {
    s[0] = '%';
    s[1] = '\0';
  } else if (format[counter] == 'c') {
    s[0] = (char)va_arg(*fact, int);
    s[1] = '\0';
  } else if (format[counter] == 'd' || format[counter] == 'i') {
    d_case(s, cases, fact);
  } else if (format[counter] == 'f') {
    f_case(s, cases, fact);
  } else if (format[counter] == 's') {
    s_case(s, cases, fact);
  } else if (format[counter] == 'u') {
    u_case(s, cases, fact);
  } else if (format[counter] == 'x') {
    x_case(s, cases, fact);
  } else if (format[counter] == 'X') {
    X_case(s, cases, fact);
  } else if (format[counter] == 'o') {
    o_case(s, cases, fact);
  } else if (format[counter] == 'n') {
    int *adr = (int *)va_arg(*fact, int *);
    (*adr) = cur_it;
  } else if (format[counter] == 'p') {
    p_case(s, cases, fact);
  } else if (format[counter] == 'g' || format[counter] == 'G') {
    g_case(s, cases, fact);
  } else if (format[counter] == 'e' || format[counter] == 'E') {
    e_case(s, cases, fact, format, counter);
  }
}
