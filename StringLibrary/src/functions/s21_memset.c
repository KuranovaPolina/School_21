#include "../s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  for (s21_size_t x = 0; x < n; x += 1) {
    ((char *)str)[x] = (char)c;
  }
  return str;
}
