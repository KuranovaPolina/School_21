#include "../s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *tmp = (char *)dest;
  char *ptr = tmp;
  char *src_p = (char *)src;
  for (s21_size_t x = 0; x < n; x++) {
    *tmp++ = *src_p++;
  }
  return ptr;
}
