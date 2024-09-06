#include <stdio.h>

#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *d = dest;
  const char *s = src;
  size_t i = 0;

  while (*d != '\0') {
    d++;
  }

  while (i < n && *s != '\0') {
    *d++ = *s++;
    i++;
  }

  *d = '\0';

  return dest;
}