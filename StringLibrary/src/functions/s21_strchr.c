#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  int x = s21_strlen(str);
  const char *result = s21_NULL;
  int nFoundStatus = 1;

  for (int i = 0; i < x && nFoundStatus; i++) {
    if ((int)(str[i]) == c) {
      nFoundStatus = 0;
      result = str + i;
    }
  }

  return (char *)result;
}
