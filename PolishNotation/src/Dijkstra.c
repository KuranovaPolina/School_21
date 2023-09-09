#include "Dijkstra.h"

int in_array(int value, const int array[]) {
  int res = 0;
  for (int i = 0; array[i] != (int)'\n' && !res; i++) {
    if (array[i] == value) {
      res = 1;
    }
  }

  return res;
}

int is_opp(char prev, char **sign) {
  const int array1[] = {40, 41, 94, 42, 47, 43, 0, (int)'\n'};
  const int array2[] = {40, 41, 115, 99, 116, 67, 83, 108,
                        94, 42, 47,  43, 45,  95, 44, (int)'\n'};

  char letter = **sign;
  int res = 0;

  if (in_array((int)letter, array1)) {
    res = letter;
  } else if (letter == '-') {
    if (in_array((int)prev, array2))
      res = 95;
    else
      res = 45;
  } else if (letter == 's') {
    if (*(*sign + 1) == 'i' && *(*sign + 2) == 'n') {
      (*sign) += 2;
      res = 115;
    } else if (*(*sign + 1) == 'q' && *(*sign + 2) == 'r' &&
               *(*sign + 3) == 't') {
      (*sign) += 3;
      res = 83;
    } else {
      res = -1;
    }

  } else if (letter == 'c') {
    if (*(*sign + 1) == 'o' && *(*sign + 2) == 's') {
      (*sign) += 2;
      res = 99;
    } else if (*(*sign + 1) == 't' && *(*sign + 2) == 'g') {
      (*sign) += 2;
      res = 67;
    } else {
      res = -1;
    }
  } else if (letter == 't') {
    if (*(*sign + 1) == 'a' && *(*sign + 2) == 'n') {
      (*sign) += 2;
      res = 116;
    } else {
      res = -1;
    }
  } else if (letter == 'l') {
    if (*(*sign + 1) == 'n') {
      (*sign) += 1;
      res = 108;
    } else {
      res = -1;
    }
  }

  return res;
}

char *Dijkstra(char *start_expr) {
  char *result_expr = malloc(1 * sizeof(char)), *stack = init(',');
  int res_size = 1, stack_size = 1;
  char prev = ',';
  const int array1[] = {115, 99, 116, 67, 83, 108, 95, (int)'\n'};

  result_expr[0] = ',';

  for (char *p = start_expr; *p; p++) {
    int opp = is_opp(prev, &p);

    if (!opp) {
      put_in_res(&result_expr, *p, &res_size);
    } else {
      char *to_res = stack_change(&stack, &stack_size, opp);
      if (in_array((int)opp, array1)) {
        put_line(&result_expr, " r ", &res_size);
      } else {
        put_in_res(&result_expr, ' ', &res_size);
      }

      for (char *r = to_res; *r != '\0'; r++) {
        put_in_res(&result_expr, ' ', &res_size);
        put_in_res(&result_expr, *r, &res_size);
        put_in_res(&result_expr, ' ', &res_size);
      }
      free(to_res);
    }

    prev = (char)opp;
  }

  while (stack_size != 1) {
    char stack_end = pop(&stack, &stack_size);
    put_in_res(&result_expr, ' ', &res_size);
    put_in_res(&result_expr, stack_end, &res_size);
  }

  result_expr[res_size] = ',';

  destroy(&stack);

  return result_expr;
}

char *stack_change(char **stack, int *stack_size, char letter) {
  char *res = NULL;
  int res_len = 0;
  char stack_output;

  if (letter == ')') {
    while (1) {
      stack_output = pop(stack, stack_size);
      if (stack_output == ',') {
        push(stack, stack_output, stack_size);
        break;
      } else if (stack_output == '(') {
        break;
      }

      put_in_res(&res, stack_output, &res_len);
    }
  } else {
    stack_output = pop(stack, stack_size);
    push(stack, stack_output, stack_size);

    if (stack_output != ',' && stack_output != '(' &&
        priority(letter) >= priority(stack_output)) {
      while (1) {
        stack_output = pop(stack, stack_size);
        if (stack_output == ',') {
          push(stack, stack_output, stack_size);
          break;
        }

        put_in_res(&res, stack_output, &res_len);
      }
    }
    push(stack, letter, stack_size);
  }

  put_in_res(&res, '\0', &res_len);

  return res;
}

int priority(char opp) {
  int res = 0;
  const int array1[] = {115, 99, 116, 67, 83, 108, 94, 95, (int)'\n'};
  const int array2[] = {42, 47, (int)'\n'};
  const int array3[] = {43, 45, (int)'\n'};

  if (in_array((int)opp, array1))
    res = 1;
  else if (in_array((int)opp, array2))
    res = 2;
  else if (in_array((int)opp, array3))
    res = 3;

  return res;
}

void put_in_res(char **expr, char letter, int *size) {
  if ((*expr) == NULL)
    *expr = malloc(sizeof(char));
  *expr = realloc(*expr, *size + 1);
  (*expr)[(*size)++] = letter;
}

void put_line(char **expr, char letter[], int *size) {
  for (int i = 0; letter[i]; i++) {
    put_in_res(expr, letter[i], size);
  }
}
