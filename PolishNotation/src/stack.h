#include <stdlib.h>
#include <stdio.h>

void push(char **stack, char i, int *size);
char pop(char **stack, int *size);
char* init(char i);
void destroy(char** stack);
// void print_stack(char* stack, int size);
