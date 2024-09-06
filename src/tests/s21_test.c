#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

int main() {
  char str3[] = "\0";
  char str4[] = "\0";
  char* res1 = s21_strchr(str3, '1');
  char* res2 = strchr(str4, '1');
  printf("7 res1 = %s, res 2 = %s\n", res1, res2);
  printf("str1 = %s\nstr2 = %s\n\n", str3, str4);
  return 0;
}
