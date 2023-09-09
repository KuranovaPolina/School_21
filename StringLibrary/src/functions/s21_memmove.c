#include <stdlib.h>

#include "../s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *tmp = (char *)malloc(n * sizeof(char));

  if (tmp != NULL) {
    int continueStatus = 1;

    for (s21_size_t x = 0; x < n && continueStatus; x++) {
      tmp[x] = ((char *)src)[x];

      if (((char *)src)[x] == 0) {
        continueStatus = 0;
      }
    }

    for (s21_size_t x = 0; x < n; x++) {
      ((char *)dest)[x] = tmp[x];
    }
    free(tmp);
  }

  return dest;
}
