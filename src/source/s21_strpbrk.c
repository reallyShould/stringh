#include <stdio.h>

#include "../s21_string.h"
char *s21_strpbrk(const char *str1, const char *str2) {
  char *ptr_sign = s21_NULL;
  while (*str1 != '\0' && ptr_sign == s21_NULL) {
    for (unsigned i = 0; str2[i] != '\0'; ++i)
      if (*str1 == str2[i]) {
        ptr_sign = (char *)str1;
        break;
      }
    str1++;
  }
  return ptr_sign;
}