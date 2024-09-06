#include <stdio.h>

#include "../s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1 = str1;
  const unsigned char *s2 = str2;
  for (s21_size_t i = 0; i < n; i++) {
    if (s1[i] < s2[i]) {
      return -1;
    } else if (s1[i] > s2[i]) {
      return 1;
    }
  }
  return 0;
}