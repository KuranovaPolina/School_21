#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;

  for (s21_size_t x = 0; res == 0 && x < n; x++) {
    res = str1[x] - str2[x];
  }

  return res;
}
