#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = s21_NULL;

  for (; *str1 && s21_strchr(str2, *str1) == s21_NULL; str1++) {
  }

  if (*str1) {
    res = (char *)str1;
  }

  return res;
}
