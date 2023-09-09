#include "canc.h"
#include "stack_int.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

int op[15] = {40, 41, 115, 99, 116, 67, 83, 108, 94, 42, 47, 43, 45, 95, 44};

double Calc(char *result_expr, double *func_x) {
  int stack_size = 0;
  int flag_first = 0;
  char *buff;
  double *stack_int = NULL;
  char operation;

  double step = (4.0 * M_PI) / 79.0;

  for (int f = 0; f < 80; f++) {
    for (long unsigned int i = 0; i < strlen(result_expr);
         i++) {                      // проходим всю строку
      char current = result_expr[i];  // текущий символ
      // printf("%c", current);
      if ((current != ' ') && (current != ',')) {
        int flag = 0;
        for (int j = 0; j < 15; j++) {  // сравниваем его со строкой операций
          if (result_expr[i] == op[j]) {  // если находим совпадение
            operation = result_expr[i];  // записываем в переменную для операций
            flag = 1;  // ставим флаг чтоы прекратить цикл для чисел
          }
        }
        if (flag == 0) {  // если символ не операция
          int kol = 0;
          if (result_expr[i] == 'x') {  // если х
            kol = 2;
            const char iks[3] = "-1";  // что выводим вместо икса // количество
            buff = (char *)malloc(
                (kol + 1) *
                sizeof(char));  // выделяем память для динамической строки
            for (int h = 0; h <= kol;
                 h++) {  // цикл для записи полного числа в буфферную строку
              buff[h] = iks[h];  // записываем -1 в буффер
            }
          } else if (result_expr[i] == 'r') {  // если r
            kol = 3;                          // количество
            const char ar[4] = "-10";  // что выводим вместо р
            buff = (char *)malloc(
                (kol + 1) *
                sizeof(char));  // выделяем память для динамической строки
            for (int h = 0; h <= kol;
                 h++) {  // цикл для записи полного числа в буфферную строку
              buff[h] = ar[h];  // записываем -10 в буффер
            }
          } else {
            int g = i;  // присваиваем адрес числа в строке префиксной записи
            while (result_expr[g] != ' ') {  // пока не пробел
              g++;
            }
            kol = g - 1 - i;  // считаем количество "разрядов" числа
            buff = (char *)malloc(
                kol * sizeof(char));  // выделяем память для динамической строки
            for (int h = 0; h <= kol;
                 h++) {  // цикл для записи полного числа в буфферную строку
              buff[h] = result_expr[i];  // посимвольная запись числа в буффер
              i++;
            }
            i--;
          }
          double num = atof(buff);  // преобразование строки в число
          free(buff);
          // printf("%s\n", buff);
          // printf("%lf\n", num);
          if (flag_first == 0) {
            stack_int = init_i(num);
            stack_size = 1;
            flag_first++;
          } else {
            // printf("%d\n", 1);
            push_i(&stack_int, num, &stack_size);
            // printf("%d\n", 1);
          }
        } else if (flag == 1) {  // если символ - операция
          double first = 0, second = 0;
          // берём из стека 2 последних числа, записываем в first и second
          first = pop_i(&stack_int, &stack_size);
          second = pop_i(&stack_int, &stack_size);
          // printf("\n%lf\n", first);
          // printf("%lf\n", second);
          if (first == -10) {
            first = 0;
          }
          double arg = 0.0 + (step * f);
          if ((second == -1) && (first == -1)) {
            second = arg;
            first = arg;
          } else if (second == -1) {
            second = arg;
            //  printf("%lf\n", first);
          } else if (first == -1) {
            first = arg;
            // printf("%lf\n", second);
          }
          push_i(&stack_int, expression(operation, &first, &second),
                 &stack_size);
        }
      }
    }
    func_x[f] = pop_i(&stack_int, &stack_size);
    destroy_i(&stack_int);
    // print_stack(stack_int, stack_size);
  }
  // printf(" ");
  // print_stack(stack_int, stack_size);
  return 0;
}

double expression(char op, double *first, double *second) {
  double result;
  switch (op) {
  case '+':
    result = *first + *second;
    break;
  case '-':
    result = *first - *second;
    break;
  case '*':
    // printf("\n%lf\n", *first);
    //   printf("%lf\n", *second);
    result = (*first) * (*second);
    // printf("%lf\n", result);
    break;
  case '/':
    result = *first / *second;
    break;
  case 's':
    result = sin(*second);
    printf("%lf\n", result);
    break;
  case 'c':
    result = cos(*second);
    break;
  case 't':
    result = tan(*second);
    break;
  case 'C':
    result = 1 / tan(*second);
    break;
  case 'S':
    result = sqrt(*second);
    break;
  case 'l':
    result = log(*second);
    break;
  case '^':
    result = pow(*first, *second);
    break;
  }
  return result;
}
