#include "../s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  // changed
  s21_size_t src_len = s21_strlen(src);
  char *buf = calloc(src_len + 1, sizeof(char)), *res = s21_NULL;
  if (buf != s21_NULL) {
    char *buf_start = buf, *buf_end = buf + src_len - 1;
    s21_strcpy(buf, src);

    while (s21_strchr(trim_chars, *buf_start)) {
      buf_start++;
    }

    while (s21_strchr(trim_chars, *buf_end)) {
      *buf_end = '\0';
      buf_end--;
    }

    res = calloc((buf_end - buf_start) + 1, sizeof(char));

    if (res) {
      s21_strcpy(res, buf_start);
    }

    free(buf);
  }

  return res ? (void *)res : s21_NULL;
}
