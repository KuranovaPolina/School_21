#include "Dijkstra.h"
#include "canc.h"
#include "stack.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void draw(const double *array);

int main() {
  char start_expr[1024];
  fgets(start_expr, 1000, stdin);
  // int i = 0;
  /*
  scanf("%c", &start_expr[i]);
  while(start_expr[i] = '\n') {
      i++;
      start_expr = (char*)malloc(sizeof(char));
      scanf("%c", &start_expr[i]);
  }*/
  double x_arr[80];
  char *result_expr = Dijkstra(start_expr);
  for (int i = 0; result_expr[i]; i++) {
    printf("%c", result_expr[i]);
  }
  printf("\n");

  Calc(result_expr, x_arr);

  draw(x_arr);

  free(result_expr);

  return 0;
}

void draw(const double *array) {
  for (int y = 0; y < 25; y++) {
    for (int x = 0; x < 80; x++) {
      if (round(12.0 * array[x] + 12.0) == y)
        printf("*");
      else
        printf(".");
    }
    printf("\n");
  }
}
