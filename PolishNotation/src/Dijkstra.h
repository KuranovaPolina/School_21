#include "stack.h"

int in_array (int value, const int array[]);
int is_opp(char prev, char **sign);
char* Dijkstra (char* start_expr);
char* stack_change(char**stack, int *stack_size, char letter);
int priority(char opp);
void put_in_res (char **expr, char letter, int *size);
void put_line(char **expr, char letter[], int *size);

    // -1 - error
    // 0 - !opp
    // 40 - (
    // 41 - )
    // 115 (s) - sin .
    // 99 (c) - cos .
    // 116 (t) - tan .
    // 67 (C) - ctg .
    // 83 (S) - sqrt .
    // 108 (l) - ln 
    // 94 - ^
    // 42 - *
    // 47 - /
    // 43 - +
    // 45 - -
    // 95 (_) - -
    // 44 (,)
