#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  int x = s21_strlen(str);
  const char *result = s21_NULL;
  int notFoundStatus = 1;

  for (; x >= 0 && notFoundStatus; x--) {
    if ((int)(str[x]) == c) {
      notFoundStatus = 0;
      result = str + x;
    }
  }

  return (char *)result;
}
