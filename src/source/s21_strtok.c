#include "../s21_string.h"

static char *ptr_sourse = s21_NULL;

char *s21_strtok(char *str, const char *delim) {
  char *return_ptr = s21_NULL;
  if (str != s21_NULL) {
    ptr_sourse = str;
    while (*ptr_sourse != '\0' &&
           (s21_strchr(delim, *ptr_sourse)))  // Поиск первого совпадения
      ptr_sourse++;
  }
  if (*ptr_sourse != '\0' && ptr_sourse != s21_NULL) {
    while (*ptr_sourse != '\0' &&
           (s21_strchr(delim, *ptr_sourse)))  // Поиск первого совпадения
      ptr_sourse++;
    return_ptr = ptr_sourse;
    if (ptr_sourse && delim) {
      while (*ptr_sourse != '\0' &&
             !(s21_strchr(delim, *ptr_sourse))) {  // Поиск первого совпадения
        ptr_sourse++;
      }
    }
    if (*ptr_sourse != '\0') {
      *ptr_sourse = '\0';  // обрезание для возвращаемой строки
      ptr_sourse++;
    }
    if (str == s21_NULL)
      if (ptr_sourse && delim) {
        while (*ptr_sourse != '\0' && (s21_strchr(delim, *ptr_sourse)))
          ptr_sourse++;
      }
  }
  return return_ptr;
}