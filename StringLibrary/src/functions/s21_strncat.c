#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0, j = 0;

  for (; dest[i]; i++) {
  }

  for (; j < n && src[j]; j++) {
    dest[i + j] = src[j];
  }

  dest[i + j] = '\0';

  return dest;
}
