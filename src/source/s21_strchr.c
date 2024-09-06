#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *out = s21_NULL;

  if (str == s21_NULL) {
    out = s21_NULL;
  } else {
    while (*str != '\0') {
      if (*str == (char)c) {
        out = (char *)str;
        break;
      }
      str++;
    }
    if (c == '\0') {
      out = (char *)str;
    }
  }
  return out;
}
