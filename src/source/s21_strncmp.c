#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int out = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i])
      out = str1[i] - str2[i];
    else {
      if (str1[i] != '\0' || str2[i] != '\0')
        continue;
      else
        break;
    }
    break;
  }
  return out;
}