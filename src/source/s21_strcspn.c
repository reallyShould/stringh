#include "../s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t out = 0;
  s21_size_t len = s21_strlen(str1);
  for (int i = 0; i < (int)len; i++) {
    if (str1[i] != str2[i]) {
      out++;
    } else {
      break;
    }
  }
  return out;
}