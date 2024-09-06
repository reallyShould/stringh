#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t len_str = s21_strlen(str);
  s21_size_t len_src = s21_strlen(src);

  if (start_index > len_src) {
    start_index = len_src;
  }

  char *s = (char *)malloc(len_src + len_str + 1);

  s21_memcpy(s, src, start_index);
  s21_memcpy(s + start_index, str, len_str);
  s21_memcpy(s + start_index + len_str, src + start_index,
             len_src - start_index);

  s[len_src + len_str] = '\0';

  return (void *)s;
}