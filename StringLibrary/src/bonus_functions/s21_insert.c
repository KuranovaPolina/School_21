#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  // changed
  s21_size_t src_len = s21_strlen(src), str_len = s21_strlen(str);
  char *res = s21_NULL;
  s21_size_t new_len =
      (start_index + str_len) > src_len ? (start_index + str_len) : src_len;

  if (start_index > src_len || str == s21_NULL) {
    res = s21_NULL;
  } else {
    res = calloc((new_len + 1), sizeof(char));

    if (res) {
      s21_strncpy(res, src, start_index);
      s21_strcat(res, str);
      s21_strcat(res, src + start_index);
    } else {
      res = s21_NULL;
    }
  }

  return res ? (void *)res : s21_NULL;
}
