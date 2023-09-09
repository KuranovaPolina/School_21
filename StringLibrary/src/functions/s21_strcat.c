#include "../s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  int i = 0, j = 0;

  for (; dest[i]; i++) {
  }

  for (; src[j]; j++) {
    dest[i + j] = src[j];
  }

  dest[i + j] = '\0';

  return dest;
}
