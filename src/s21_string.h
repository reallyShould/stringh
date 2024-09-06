#ifndef S21_STRING_H
#define S21_STRING_H

typedef long unsigned s21_size_t;

#define s21_NULL ((void *)0)

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int s21_sprintf(char *str, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);  // test on mac
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

int read_and_wright(va_list args, const char **str, int *result, const char **p,
                    int length, int width, const char *start, int back);
int read_but_not_wright(const char **str, const char **p, int length,
                        int *width);
int parsing_width(const char **p);
int parsing_length(const char **p);
int s_specifier(void *sp, const char **str, int *result, int *width);
int c_specifier(void *cp, const char **str, int *result, int *width);
int d_specifier(void *dp, const char **str, int *result, int length,
                int *width);
int u_specifier(void *up, const char **str, int *result, int length,
                int *width);
int i_specifier(const char **str);
int x_specifier(void *xp, const char **str, int *result, int length,
                int *width);
void x_specifier_parser(unsigned int *digit, const char **str, int *width,
                        int *back);
void lx_specifier_parser(unsigned long int *digit, const char **str, int *width,
                         int *back);
void hx_specifier_parser(unsigned short int *digit, const char **str,
                         int *width, int *back);
int o_specifier(void *op, const char **str, int *result, int length,
                int *width);
void o_specifier_parser(unsigned int *digit, const char **str, int *width,
                        int *back);
void lo_specifier_parser(unsigned long int *digit, const char **str, int *width,
                         int *back);
void ho_specifier_parser(unsigned short int *digit, const char **str,
                         int *width, int *back);
const char *n_specifier(void *np, const char **str, const char *start);
int f_specifier(void *fp, const char **str, int *result, int length,
                int *width);
int f_specifier_parser(float *digit, const char **str, int *width);
int Lf_specifier_parser(long double *digit, const char **str, int *width);
int g_specifier(void *gp, const char **str, int *result, int length,
                int *width);
int g_specifier_parser(float *digit, const char **str, int *width);
int Lg_specifier_parser(long double *digit, const char **str, int *width);
int skip_math_sign(const char **str, int *width, int sign);
#endif