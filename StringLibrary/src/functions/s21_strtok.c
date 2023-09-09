#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last_ptr = s21_NULL;
  char *start = str ? str : last_ptr;
  int flag = 1;

  if (!start) {
    flag = 0;
  }

  if (flag) {
    start += s21_strspn(start, delim);
    if (*start == '\0') {
      last_ptr = s21_NULL;
      flag = 0;
    }

    if (flag) {
      char *end = start + s21_strcspn(start, delim);
      if (*end == '\0') {
        last_ptr = s21_NULL;
      } else {
        *end = '\0';
        last_ptr = end + 1;
      }
    }
  }

  return (start && *start != '\0') ? start : s21_NULL;
}
