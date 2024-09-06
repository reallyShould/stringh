#include <stdio.h>

#include "../s21_string.h"

char *first_use_strtok(char *str, const char *delim, char *ptr_sourse,
                       char **ptr, unsigned *i, unsigned *tok);
char *next_use_strtok(const char *delim, char *ptr_sourse, char **ptr,
                      unsigned *i, unsigned *tok);
short find_delim(char *str, const char *delim, unsigned *i, unsigned *tok);

static char *ptr_sourse;

char *s21_strtok(char *str, const char *delim) {
  char *ptr = s21_NULL;
  unsigned tok = 0;
  unsigned i = 0;
  if (str != s21_NULL) {
    if (find_delim(str, delim, &i, &tok)) {
      ptr_sourse = first_use_strtok(str, delim, ptr_sourse, &ptr, &i, &tok);
    }
  } else {
    if (find_delim(ptr_sourse, delim, &i, &tok)) {
      ptr_sourse = next_use_strtok(delim, ptr_sourse, &ptr, &i, &tok);
    }
  }
  return ptr;
}

short find_delim(char *str, const char *delim, unsigned *i, unsigned *tok) {
  short flag_delim = 0;
  while (str[*i] != '\0') {
    flag_delim = 0;
    for (unsigned j = 0; delim[j] != '\0'; ++j) {
      if (str[*i] == delim[j]) {
        flag_delim = 1;
        break;
      }
    }
    if (flag_delim == 0) {
      flag_delim = 1;
      *tok = *i;
      if (str[(*i) + 1] != '\0') ++i;
      break;
    }
    ++(*i);
  }
  return flag_delim;
}

char *first_use_strtok(char *str, const char *delim, char *ptr_sourse,
                       char **ptr, unsigned *i, unsigned *tok) {
  short flag_delim = 1;
  while (str[*i] != '\0' && flag_delim == 1) {
    for (unsigned j = 0; delim[j] != '\0'; ++j) {
      if (str[*i] == delim[j] ||
          (str[(*i) + 1] == '\0' && str[*i] != delim[j])) {
        flag_delim = 0;
        break;
      }
    }
    if (flag_delim == 0) {
      short lust_delim = 0;
      ptr_sourse = &str[(*i) + 1];
      for (unsigned j = 0; delim[j] != '\0'; ++j)
        if (str[*i] == delim[j]) lust_delim = 1;
      if (str[(*i) + 1] != '\0' || lust_delim == 1) str[*i] = '\0';
      *ptr = &str[*tok];
    }
    ++(*i);
  }
  return ptr_sourse;
}

char *next_use_strtok(const char *delim, char *ptr_sourse, char **ptr,
                      unsigned *i, unsigned *tok) {
  short flag_delim = 1;
  while (ptr_sourse[*i] != '\0' && flag_delim == 1) {
    flag_delim = 1;
    for (unsigned j = 0; delim[j] != '\0'; ++j) {
      if (ptr_sourse[*i] == delim[j] || ptr_sourse[(*i) + 1] == '\0') {
        flag_delim = 0;
        break;
      }
    }
    if (flag_delim == 0) {
      short lust_delim = 0;
      char *ptr_interim = s21_NULL;
      ptr_interim = ptr_sourse;
      ptr_sourse = &ptr_sourse[(*i) + 1];
      if (ptr_sourse[(*i) + 1] == '\0' || ptr_interim[(*i) + 1] == '\0')
        for (unsigned j = 0; delim[j] != '\0'; ++j)
          if (ptr_interim[*i] == delim[j]) lust_delim = 1;
      if (ptr_interim[(*i) + 1] != '\0' || lust_delim == 1)
        ptr_interim[*i] = '\0';
      *ptr = &ptr_interim[*tok];
      ptr_interim = s21_NULL;
      break;
    }
    ++(*i);
  }
  return ptr_sourse;
}