#include "../s21_string.h"
// #include <stdlib.h>

void *s21_to_upper(const char *str) {
  s21_size_t str_len = s21_strlen(str);

  char *res = malloc((str_len + 1) * sizeof(char));

  if (res) {
    for (s21_size_t i = 0; i < str_len; i++) {
      res[i] = (str[i] >= 'a' && str[i] <= 'z') ? (str[i] - 32) : str[i];
    }
    res[str_len] = '\0';
  } else {
    res = s21_NULL;
  }

  return (void *)res;
}
