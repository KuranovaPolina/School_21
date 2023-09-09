#include "../s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const char *_str1 = str1, *_str2 = str2;
  int res = 0;

  for (s21_size_t x = 0; res == 0 && x < n; x++) {
    res = _str1[x] - _str2[x];
  }

  return res;
}
