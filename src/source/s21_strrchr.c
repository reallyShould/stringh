#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *ptr_sign = s21_NULL;
  while (*str != '\0') {
    if (*str == (char)c) ptr_sign = (char *)str;
    str++;
  }
  return ptr_sign;
}