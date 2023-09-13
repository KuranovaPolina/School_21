#include "stack.h"

int push(struct stack_255 *stack, struct leksema value) {
  if (stack->stack_count < 255) {
    stack->stack[stack->stack_count] = value;
    stack->stack_count++;
    return 0;
  } else {
    return 1;
  }
}

int pop(struct stack_255 *stack, struct leksema *value) {
  if (stack->stack_count > 0) {
    stack->stack_count--;
    *value = stack->stack[stack->stack_count];
    return 0;
  } else {
    return 1;
  }
}

int top(struct stack_255 *stack, struct leksema *value) {
  if (stack->stack_count > 0) {
    *value = stack->stack[stack->stack_count - 1];
    return 0;
  } else {
    return 1;
  }
}
