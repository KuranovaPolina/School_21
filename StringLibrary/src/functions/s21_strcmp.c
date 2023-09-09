#include "../s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
  int res = 0, continueStatus = 1;

  for (s21_size_t x = 0; res == 0 && continueStatus; x++) {
    res = str1[x] - str2[x];
    if (!str1[x] || !str2[x]) continueStatus = 0;
  }

  return res;
}
