#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"

//mod -> %
//cos -> c
//sin -> s
//tan -> t
//acos -> C
//asin -> S
//atan -> T
//sqrt -> q
//ln -> l
//log -> L

int calculate (const char *str, char *str_result, double X);
int mathCalculate(struct stack_255 *stack_num, struct stack_255 *stack_opp);
int getRang (char opp);

#endif // CALCULATOR_H
