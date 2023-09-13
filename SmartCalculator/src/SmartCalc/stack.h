#ifndef STACK_H
#define STACK_H

struct leksema {
    char type;
    double value;
};

struct stack_255 {
    struct leksema stack[255];
    int stack_count;
};

int push(struct stack_255 *stack, struct leksema value);
int pop(struct stack_255 *stack, struct leksema *value);
int top(struct stack_255 *stack, struct leksema *value);

#endif // STACK_H
