#include "stack.h"

void push(char **stack, char i, int *size) {
  *stack = realloc(*stack, ++(*size));
  (*stack)[(*size) - 1] = i;
}

char pop(char **stack, int *size) {
  char res = (*stack)[--(*size)];
  if (*size == 0)
    destroy(stack);
  else
    *stack = realloc(*stack, *size);

  return res;
}

char *init(char i) {
  char *stack = malloc(sizeof(char));
  stack[0] = i;
  return stack;
}

void destroy(char **stack) {
  free(*stack);
  *stack = NULL;
}

/*
void print_stack(char* stack, int size) {
    if (size) {
        for (int i = 0; i < size; i++) {
            printf("%c.", stack[i]);
            if (i == size - 1) printf("\n");
            else
                printf(" ");
        }
    } else {
        printf("\n"); }
} */
