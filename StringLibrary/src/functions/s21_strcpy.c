#include "../s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  int continueStatus = 1;

  for (s21_size_t x = 0; continueStatus; x += 1) {
    dest[x] = ((char *)src)[x];

    if (((char *)src)[x] == 0) {
      continueStatus = 0;
    }
  }
  return dest;
}
