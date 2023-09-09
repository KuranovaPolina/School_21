#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const char *result = str;
  int notFoundStatus = 1;

  for (s21_size_t x = 0; notFoundStatus && x < n; x++) {
    if ((int)(result[x]) == c) {
      result += x;
      notFoundStatus = 0;
    }
  }

  return !notFoundStatus ? (void *)result : s21_NULL;
}
