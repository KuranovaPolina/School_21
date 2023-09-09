#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *res = s21_NULL;
  int continueStatus = 1;
  while (*haystack && continueStatus) {
    char *tmp1 = (char *)haystack;
    char *tmp2 = (char *)needle;
    while (*haystack && *tmp2 && *haystack == *tmp2) {
      haystack++;
      tmp2++;
    }
    if (!*tmp2) {
      continueStatus = 0;
      res = tmp1;
    }

    haystack = tmp1 + 1;
  }
  return res ? res : s21_NULL;
}
