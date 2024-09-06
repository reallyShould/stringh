#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == s21_NULL || trim_chars == s21_NULL) {
    return s21_NULL;
  }

  s21_size_t len = s21_strlen(src);
  s21_size_t start = 0;
  s21_size_t end = len - 1;

  while (start <= end && s21_strchr(trim_chars, src[start])) {
    start++;
  }

  while (end >= start && s21_strchr(trim_chars, src[end])) {
    end--;
  }

  s21_size_t new_len = end - start + 1;

  char *trimmed_str = (char *)malloc(new_len + 1);
  if (trimmed_str == s21_NULL) {
    return s21_NULL;
  }

  s21_strncpy(trimmed_str, src + start, new_len);
  trimmed_str[new_len] = '\0';

  return trimmed_str;
}