#include "calculator.h"

int calculate(const char *str, char *str_result, double X) {
  // error = 0 - OK
  // error = 1 - INCORRECT EXPRESSION
  // error = 2 - PARENTHESIS ERROR
  // error = 3 - CALCULATION ERROR
  // error = 4 - INF

  char ch;
  int flag_un = 1;

  int error = 0;

  struct leksema item;
  struct stack_255 stack_num = {{0}, 0};
  struct stack_255 stack_opp = {{0}, 0};

  int left_br_count = 0, right_br_count = 0;

  ch = str[strlen(str) - 1];

  if (!((ch >= '0' && ch <= '9') || ch == ')' || ch == 'X')) {
    error = 1;
  }

  for (int i = 0; i < (int)strlen(str) && error == 0; i++) {
    ch = str[i];

    if (ch == 'm' || ch == 'c' || ch == 's' || ch == 't' || ch == 'a' ||
        ch == 'l') {
      if (ch == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') {
        flag_un = 1;
        struct leksema top_opp;
        top(&stack_opp, &top_opp);
        ch = '%';

        if (stack_opp.stack_count == 0) {
          i += 2;

          item.type = ch;
          item.value = 0;

          push(&stack_opp, item);
        } else if (stack_opp.stack_count != 0 &&
                   getRang(ch) > getRang(top_opp.type)) {
          i += 2;
          item.type = ch;
          item.value = 0;

          push(&stack_opp, item);
        } else if (stack_opp.stack_count != 0 &&
                   getRang(ch) <= getRang(top_opp.type)) {
          mathCalculate(&stack_num, &stack_opp);
          i--;
        }
      } else if (ch == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') {
        i += 2;

        item.type = 'c';
        item.value = 0;

        push(&stack_opp, item);
        flag_un = 1;
      } else if (ch == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') {
        i += 2;

        item.type = 's';
        item.value = 0;

        push(&stack_opp, item);
        flag_un = 1;
      } else if (ch == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') {
        i += 2;

        item.type = 't';
        item.value = 0;

        push(&stack_opp, item);
        flag_un = 1;
      } else if (ch == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
                 str[i + 3] == 's') {
        i += 3;

        item.type = 'C';
        item.value = 0;

        push(&stack_opp, item);
        flag_un = 1;
      } else if (ch == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
                 str[i + 3] == 'n') {
        i += 3;

        item.type = 'S';
        item.value = 0;

        push(&stack_opp, item);
        flag_un = 1;
      } else if (ch == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
                 str[i + 3] == 'n') {
        i += 3;

        item.type = 'T';
        item.value = 0;

        push(&stack_opp, item);
        flag_un = 1;
      } else if (ch == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
                 str[i + 3] == 't') {
        i += 3;

        item.type = 'q';
        item.value = 0;

        push(&stack_opp, item);
        flag_un = 1;
      } else if (ch == 'l' && str[i + 1] == 'n') {
        i += 1;

        item.type = 'l';
        item.value = 0;

        push(&stack_opp, item);
        flag_un = 1;
      } else if (ch == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g') {
        i += 2;

        item.type = 'L';
        item.value = 0;

        push(&stack_opp, item);
        flag_un = 1;
      } else {
        error = 1;
      }

    } else if ((ch == '-' && flag_un == 1) || (ch == '+' && flag_un == 1)) {
      flag_un = 1;
      if (ch == '-') {
        item.type = '_';
        item.value = 0;

        push(&stack_opp, item);
      }
    } else if (ch >= '0' && ch <= '9') {
      int num_addr = i, num_len = 0;

      int dot_count = 0;

      flag_un = 0;

      while (str[num_addr] != '\n' &&
             ((str[num_addr] == '.') ||
              (str[num_addr] >= '0' && str[num_addr] <= '9'))) {
        if (str[num_addr] == '.') {
          dot_count++;
        }
        num_addr++;
      }

      if (dot_count > 1) {
        error = 1;
      }

      num_len = num_addr - 1 - i;
      char *buff = (char *)malloc(num_len * sizeof(char));

      for (int h = 0; h <= num_len; h++) {
        buff[h] = str[i]; // посимвольная запись числа в буффер
        i++;
      }
      i--;

      double num = atof(buff); // преобразование строки в число
      free(buff);

      item.type = 0;
      item.value = num;

      push(&stack_num, item);
    } else if (ch == 'X') {
      flag_un = 0;
      item.type = 0;
      item.value = X;

      push(&stack_num, item);
    } else if ((ch == '+' && flag_un == 0) || (ch == '-' && flag_un == 0) ||
               ch == '*' || ch == '/' || ch == '^') {
      struct leksema top_opp;
      top(&stack_opp, &top_opp);

      flag_un = 1;

      if (stack_opp.stack_count == 0) {
        item.type = ch;
        item.value = 0;

        push(&stack_opp, item);
      } else if (stack_opp.stack_count != 0 &&
                 getRang(ch) > getRang(top_opp.type)) {
        item.type = ch;
        item.value = 0;

        push(&stack_opp, item);
      } else if (stack_opp.stack_count != 0 &&
                 getRang(ch) <= getRang(top_opp.type)) {
        mathCalculate(&stack_num, &stack_opp);
        i--;

        flag_un = 0;
      }

    } else if (ch == '(') {
      item.type = ch;
      item.value = 0;

      push(&stack_opp, item);
      flag_un = 1;
      left_br_count++;
    } else if (ch == ')') {
      if (right_br_count + 1 > left_br_count) {
        error = 2;
      } else {
        struct leksema top_opp;
        top(&stack_opp, &top_opp);
        while (error == 0 && top_opp.type != '(') {
          if (mathCalculate(&stack_num, &stack_opp) == 0) {
            top(&stack_opp, &top_opp);
          } else {
            error = 3;
          }
        }
        if (error == 0) {
          pop(&stack_opp, &top_opp);
          flag_un = 0;
          left_br_count--;
        }
      }
    } else {
      error = 1;
    }
  }

  while (error == 0 && stack_opp.stack_count != 0) {
    if (mathCalculate(&stack_num, &stack_opp) == 0) {
      struct leksema top_opp;
      top(&stack_opp, &top_opp);
    } else {
      error = 3;
    }
  }

  if (error == 0) {
    struct leksema res_lek;
    pop(&stack_num, &res_lek);
    double res_double = res_lek.value;
    char res[256];

    sprintf(res, "%.8lg", res_double);

    if (strcmp(res, "inf") == 0 || strcmp(res, "-inf") == 0) {
      error = 4;
    }

    strcpy(str_result, res);
  } else if (error == 1) {
    strcpy(str_result, "INCORRECT EXPRESSION");
  } else if (error == 2) {
    strcpy(str_result, "PARENTHESIS ERROR");
  } else if (error == 3) {
    strcpy(str_result, "CALCULATION ERROR");
  }

  return error;
}

int mathCalculate(struct stack_255 *stack_num, struct stack_255 *stack_opp) {
  int error = 0;

  struct leksema num_lek_1, num_lek_2, opp_lek;
  struct leksema item;
  pop(stack_num, &num_lek_1);
  pop(stack_opp, &opp_lek);

  double num_1 = num_lek_1.value;
  double num_2 = 0, res = 0;

  switch (opp_lek.type) {
  case '+':
    pop(stack_num, &num_lek_2);
    num_2 = num_lek_2.value;
    res = num_1 + num_2;

    item.type = 0;
    item.value = res;

    push(stack_num, item);

    break;
  case '-':
    pop(stack_num, &num_lek_2);
    num_2 = num_lek_2.value;
    res = num_2 - num_1;

    item.type = 0;
    item.value = res;

    push(stack_num, item);

    break;
  case '*':
    pop(stack_num, &num_lek_2);
    num_2 = num_lek_2.value;
    res = num_1 * num_2;

    item.type = 0;
    item.value = res;

    push(stack_num, item);

    break;
  case '/':
    pop(stack_num, &num_lek_2);
    num_2 = num_lek_2.value;
    if (num_1 == 0) {
      error = 1;
    } else {
      res = num_2 / num_1;

      item.type = 0;
      item.value = res;

      push(stack_num, item);
    }

    break;
  case '^':
    pop(stack_num, &num_lek_2);
    num_2 = num_lek_2.value;

    res = pow(num_2, num_1);
    item.type = 0;
    item.value = res;

    push(stack_num, item);

    break;
  case '%':
    pop(stack_num, &num_lek_2);
    num_2 = num_lek_2.value;
    if (!(fabs(num_1 - (int)(num_1)) < 10e-7 &&
          fabs(num_2 - (int)(num_2)) < 10e-7 && num_1 != 0)) {
      error = 1;
    } else {
      res = (int)num_2 % (int)num_1;

      item.type = 0;
      item.value = res;

      push(stack_num, item);
    }

    break;
  case 'c':
    res = cos(num_1);

    item.type = 0;
    item.value = res;

    push(stack_num, item);
    break;

  case 's':
    res = sin(num_1);

    item.type = 0;
    item.value = res;

    push(stack_num, item);
    break;

  case 't':
    if (cos(num_1) == 0) {
      error = 1;
    } else {
      res = tan(num_1);

      item.type = 0;
      item.value = res;

      push(stack_num, item);
    }

    break;

  case 'C':
    if (num_1 > 1 || num_1 < -1) {
      error = 1;
    } else {
      res = acos(num_1);

      item.type = 0;
      item.value = res;

      push(stack_num, item);
    }

    break;

  case 'S':
    if (num_1 > 1 || num_1 < -1) {
      error = 1;
    } else {
      res = asin(num_1);

      item.type = 0;
      item.value = res;

      push(stack_num, item);
    }

    break;

  case 'T':

    res = atan(num_1);

    item.type = 0;
    item.value = res;

    push(stack_num, item);

    break;

  case 'q':
    if (num_1 < 0) {
      error = 1;
    } else {
      res = sqrt(num_1);

      item.type = 0;
      item.value = res;

      push(stack_num, item);
    }

    break;
  case 'l':
    if (num_1 <= 0) {
      error = 1;
    } else {
      res = log(num_1);

      item.type = 0;
      item.value = res;

      push(stack_num, item);
    }

    break;

  case 'L':
    if (num_1 <= 0) {
      error = 1;
    } else {
      res = log10(num_1);

      item.type = 0;
      item.value = res;

      push(stack_num, item);
    }

    break;

  case '_':

    res = -1 * num_1;

    item.type = 0;
    item.value = res;

    push(stack_num, item);

    break;

  case '(':
    item.type = 0;
    item.value = num_1;

    push(stack_num, item);

    break;

  default:
    break;
  }

  return error;
}

int getRang(char opp) {
  int res = 0;
  if (opp == '+' || opp == '-') {
    res = 1;
  } else if (opp == '*' || opp == '/' || opp == '%') {
    res = 2;
  } else if (opp == '^') {
    res = 3;
  } else if (opp == 'c' || opp == 's' || opp == 't' || opp == 'C' ||
             opp == 'S' || opp == 'T' || opp == 'q' || opp == 'l' ||
             opp == 'L' || opp == '_') {
    res = 4;
  }

  return res;
}
