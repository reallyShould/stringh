#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

void *s21_to_lower(const char *str) {
  char *s = (char *)malloc(s21_strlen(str) + 1);

  for (int i = 0; str[i] != '\0'; i++) {
    s[i] = tolower((unsigned char)str[i]);
  }
  s[s21_strlen(str)] = '\0';
  return (void *)s;
}