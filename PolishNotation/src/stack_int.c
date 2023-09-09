#include "stack_int.h"

void push_i(double **stack, double i, int *size) {
  *stack = realloc(*stack, ++(*size));
  (*stack)[(*size) - 1] = i;
}

double pop_i(double **stack, int *size) {
  double res = (*stack)[--(*size)];
  if (*size == 0)
    destroy_i(stack);
  else
    *stack = realloc(*stack, *size);

  return res;
}

double *init_i(double i) {
  double *stack = malloc(sizeof(double));
  stack[0] = i;
  return stack;
}

void destroy_i(double **stack) {
  free(*stack);
  *stack = NULL;
}
