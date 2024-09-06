#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#include "../s21_string.h"

char buffer[500] = {0};

void spase_after_or_before(
    int *width, int *count,
    char **str) {  // пробелы после текста и выравнивание слева
  if (*width) {
    for (; *width; (void)(*width)--) {
      (*count)++;
      **str = ' ';
      (*str)++;
    }
  }
}

void letter_cpy(char **str, int *letter, int *width_right, int *width_left,
                int *count) {
  if (*width_left && *letter != 0) (*width_left)--;
  spase_after_or_before(width_left, count,
                        str);  // пробелы перед текстом и выравнивание справа
  **str = *letter;
  (*str)++;
  (*count)++;
  if (*width_right) (*width_right)--;
  spase_after_or_before(width_right, count,
                        str);  // пробелы после текста и выравнивание слева
}

void str_cpy(char **str, char **string, int *width_right, int *width_left,
             int *count) {
  for (int i = 0; (*string)[i] != '\0'; ++i) {
    if (*width_left) (*width_left)--;
  }
  spase_after_or_before(width_left, count,
                        str);  // пробелы перед текстом и выравнивание справа
  while (**string != '\0') {
    **str = **string;
    (*str)++;
    (*string)++;
    (*count)++;
    if (*width_right) (*width_right)--;
  }
  spase_after_or_before(width_right, count,
                        str);  // пробелы после текста и выравнивание слева
}

void int_to_str(int num, char **str, int *count, int *width_right,
                int width_left) {
  int len = 0;
  int negative = 0;
  if (num < 0) {
    negative = 1;
    num = -num;
    (*count)++;  // Счётчик количества записей в str
    if (width_left) width_left--;  // Счётчик для пробелов перед текстом
    if (*width_right) (*width_right)--;  // Счётчик для пробелов после текста
  }

  if (width_left) {  //  Ветка для пробелов перед текстом
    int spase = num;
    while (spase && width_left) {
      spase /= 10;
      width_left--;
    }
    spase_after_or_before(&width_left, count,
                          str);  // пробелы перед текстом и выравнивание справа
  }

  do {
    (*str)[len++] = '0' + num % 10;
    num /= 10;
    (*count)++;  // Счётчик количества записей в str
    if (*width_right) (*width_right)--;  // Счётчик для пробелов после текста
  } while (num != 0);

  if (negative == 1) {
    (*str)[len++] = '-';
  }

  for (int i = 0; i < len / 2; i++) {
    char temp = (*str)[i];
    (*str)[i] = (*str)[len - i - 1];
    (*str)[len - i - 1] = temp;
  }
}

void long_int_u_to_str(unsigned long int num, char **str, int *count,
                       int *width_right, int width_left) {
  int len = 0;

  if (width_left) {  //  Ветка  для пробелов после текста
    unsigned long int spase = num;
    while (spase && width_left) {
      spase /= 10;
      width_left--;
    }
    spase_after_or_before(&width_left, count,
                          str);  // пробелы перед текстом и выравнивание справа
  }

  do {
    (*str)[len++] = '0' + num % 10;
    num /= 10;
    (*count)++;  // Счётчик количества записей в str
    if (*width_right) (*width_right)--;  // Счётчик для пробелов после текста
  } while (num != 0);

  for (int i = 0; i < len / 2; i++) {
    char temp = (*str)[i];
    (*str)[i] = (*str)[len - i - 1];
    (*str)[len - i - 1] = temp;
  }
}

void short_int_u_to_str(unsigned short int num, char **str, int *count,
                        int *width_right, int width_left) {
  int len = 0;

  if (width_left) {  //  Ветка  для пробелов перед текстом
    unsigned short int spase = num;
    while (spase && width_left) {
      spase /= 10;
      width_left--;
    }
    spase_after_or_before(&width_left, count,
                          str);  // пробелы перед текстом и выравнивание справа
  }

  do {
    (*str)[len++] = '0' + num % 10;
    num /= 10;
    (*count)++;  // Счётчик количества записей в str
    if (*width_right) (*width_right)--;  // Счётчик для пробелов после текста
  } while (num != 0);

  for (int i = 0; i < len / 2; i++) {
    char temp = (*str)[i];
    (*str)[i] = (*str)[len - i - 1];
    (*str)[len - i - 1] = temp;
  }
}

void long_int_to_str(long int num, char **str, int *count, int *width_right,
                     int width_left) {
  int len = 0;
  long int negative = 0L;
  if (num < 0) {
    negative = 1;
    num = -num;
    (*count)++;  // Счётчик количества записей в str
    if (width_left) width_left--;  // Счётчик для пробелов перед текстом
    if (*width_right) (*width_right)--;  // Счётчик для пробелов после текста
  }

  if (width_left) {  //  Ветка  для пробелов перед текстом
    long int spase = num;
    while (spase && width_left) {
      spase /= 10L;
      width_left--;
    }
    spase_after_or_before(&width_left, count,
                          str);  // пробелы перед текстом и выравнивание справа
  }

  do {
    (*str)[len++] = '0' + num % 10L;
    num /= 10L;
    (*count)++;  // Счётчик количества записей в str
    if (*width_right) (*width_right)--;  // Счётчик для пробелов после текста
  } while (num != 0);

  if (negative == 1) {
    (*str)[len++] = '-';
  }

  for (int i = 0; i < len / 2; i++) {
    char temp = (*str)[i];
    (*str)[i] = (*str)[len - i - 1];
    (*str)[len - i - 1] = temp;
  }
}

void short_int_to_str(short int num, char **str, int *count, int *width_right,
                      int width_left) {
  int len = 0;
  short int negative = 0;
  if (num < 0) {
    negative = 1;
    num = -num;
    (*count)++;  // Счётчик количества записей в str
    if (width_left) width_left--;  // Счётчик для пробелов перед текстом
    if (*width_right) (*width_right)--;  // Счётчик для пробелов после текста
  }

  if (width_left) {  //  Ветка  для пробелов перед текстом
    short int spase = num;
    while (spase && width_left) {
      spase /= 10;
      width_left--;
    }
    spase_after_or_before(&width_left, count,
                          str);  // пробелы перед текстом и выравнивание справа
  }

  do {
    (*str)[len++] = '0' + num % 10;
    num /= 10;
    (*count)++;  // Счётчик количества записей в str
    if (*width_right) (*width_right)--;  // Счётчик для пробелов после текста
  } while (num != 0);

  if (negative == 1) {
    (*str)[len++] = '-';
  }

  for (int i = 0; i < len / 2; i++) {
    char temp = (*str)[i];
    (*str)[i] = (*str)[len - i - 1];
    (*str)[len - i - 1] = temp;
  }
}

void space_to_float(float num, char **str, int *precision, int *count,
                    int width_left) {
  int len = 0;
  if (width_left) {  // Ветка для пробелов перед текстом
    int WholePart1 = (int)num;
    double decimalPart1 = num - WholePart1;
    int precision1 = *precision;
    while (WholePart1 != 0 && width_left) {
      if (width_left) width_left--;  // Счётчик для пробелов перед текстом
      WholePart1 /= 10;
      len++;
    }
    if (width_left) width_left--;  // Счётчик для пробелов перед текстом
    len++;
    if (precision1 > 0) {
      while (precision1 > 0 && width_left) {
        decimalPart1 *= 10;
        int digit = (int)decimalPart1;
        if (width_left) width_left--;  // Счётчик для пробелов перед текстом
        decimalPart1 -= digit;
        precision1--;
        len++;
      }
    } else {
      while (len < 8 && width_left) {
        decimalPart1 *= 10;
        int digit = round(decimalPart1);
        if (width_left) width_left--;  // Счётчик для пробелов перед текстом
        decimalPart1 -= digit;
        len++;
      }
    }
    spase_after_or_before(&width_left, count,
                          str);  // пробелы перед текстом и выравнивание справа
  }
}

char *float_to_str(float num, char **str, int *precision, int *count,
                   int *width_right, int width_left) {
  int len = 0, negative = 0, WholePart = 0;
  if (num < 0) {
    negative = 1;
    num = -num;
    (*count)++;  // Счётчик количества записей в str
    if (width_left) width_left--;  // Счётчик для пробелов перед текстом
    if (*width_right) (*width_right)--;  // Счётчик для пробелов после текста
  }
  WholePart = (int)num;
  double decimalPart = num - WholePart;
  space_to_float(num, str, precision, count, width_left);
  if (negative == 1) {
    (**str) = '-';
    (*str)++;
  }
  while (WholePart != 0) {
    (*str)[len++] = '0' + WholePart % 10;
    WholePart /= 10;
    (*count)++;  // Счётчик количества записей в str
    if (*width_right) (*width_right)--;  // Счётчик для пробелов перед текстом
  }
  (*str)[len++] = '.';
  (*count)++;
  if (*width_right) (*width_right)--;  // Счётчик для пробелов перед текстом
  if (*precision > 0) {
    while (*precision > 0) {
      decimalPart *= 10;
      int digit = (int)decimalPart;
      (*str)[len++] = '0' + digit % 10;
      decimalPart -= digit;
      (*precision)--;
      (*count)++;  // Счётчик количества записей в str
      if (*width_right) (*width_right)--;  // Счётчик для пробелов перед текстом
    }
  } else {
    while (len < 8) {
      decimalPart *= 10;
      int digit = round(decimalPart);
      (*str)[len++] = '0' + digit % 10;
      decimalPart -= digit;
      (*count)++;  // Счётчик количества записей в str
      if (*width_right) (*width_right)--;  // Счётчик для пробелов перед текстом
    }
  }
  for (int i = 0; i < len; ++i)
    (*str)++;  // Шагает по строке, что бы вернуть адрес
  return (*str);
}

const char *length_str(const char *format, int *length) {
  if (*format == 'h') {
    *length = -1;
    format++;
  }
  if (*format == 'l') {
    *length = 1;
    format++;
  }
  return format;
}

const char *precision_str(const char *format, int *precision) {
  if (*format == '.') {
    format++;
    *precision = *format - '0';
    format++;
  } else {
    precision = 0;
  }
  return format;
}

char *spec_d(char **str, va_list args, int *length, int *count,
             int *width_right, int width_left) {
  if (*length == 1) {
    long int num_l = va_arg(args, long int);
    long_int_to_str(num_l, str, count, width_right, width_left);
    if (num_l < 0) (*str)++;
    while (num_l != 0) {
      num_l /= 10;
      (*str)++;
    }
  } else if (*length == -1) {
    short int num_h = va_arg(args, int);
    short_int_to_str(num_h, str, count, width_right, width_left);
    if (num_h < 0) (*str)++;
    while (num_h != 0) {
      num_h /= 10;
      (*str)++;
    }
  } else {
    int num = va_arg(args, int);
    int_to_str(num, str, count, width_right, width_left);
    if (num < 0) (*str)++;
    while (num != 0) {
      num /= 10;
      (*str)++;
    }
  }
  return *str;
}

char *spec_u(char **str, va_list args, int *length, int *count,
             int *width_right, int width_left) {
  if (*length == 1) {
    unsigned long int num_l = va_arg(args, unsigned long int);
    long_int_u_to_str(num_l, str, count, width_right, width_left);
    while (num_l != 0) {
      num_l /= 10;
      (*str)++;
    }
  } else if (*length == -1) {
    unsigned short int num_h = va_arg(args, unsigned int);
    short_int_u_to_str(num_h, str, count, width_right, width_left);
    while (num_h != 0) {
      num_h /= 10;
      (*str)++;
    }
  } else {
    unsigned int num_u = va_arg(args, unsigned int);
    int_to_str(num_u, str, count, width_right, width_left);
    while (num_u != 0) {
      num_u /= 10;
      (*str)++;
    }
  }
  return *str;
}

const char *spec_check(const char *format, va_list args, char **str,
                       int *length, int *precision, int *count, int width_right,
                       int width_left) {
  switch (*format) {
    case 'c': {
      int letter = va_arg(args, int);
      letter_cpy(str, &letter, &width_right, &width_left, count);
      break;
    }
    case 'd': {
      *str =
          spec_d(str, args, length, count, &width_right,
                 width_left);  // Функция возвращает количество шагов в строку
      spase_after_or_before(&width_right, count,
                            str);  // пробелы после текста и выравнивание слева
      break;
    }
    case 'f': {
      double float_num = va_arg(args, double);
      *str = float_to_str(float_num, str, precision, count, &width_right,
                          width_left);
      spase_after_or_before(&width_right, count,
                            str);  // пробелы после текста и выравнивание слева
      break;
    }
    case 'u': {
      *str = spec_u(str, args, length, count, &width_right, width_left);
      spase_after_or_before(&width_right, count,
                            str);  // пробелы после текста и выравнивание слева
      break;
    }
    case 's': {
      char *string = va_arg(args, char *);
      str_cpy(str, &string, &width_right, &width_left, count);
      break;
    }
    case '%': {
      **str = '%';
      (*str)++;
      (*count)++;
      break;
    }
  }
  return format;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int width_left = 0;
  int precision = 0;
  int width_right = 0;
  int length = 0;
  int count = 0;

  for (size_t i = 0; i < sizeof(char) * 500; ++i) {
    str[i] = 0;
  }
  for (; *format != '\0'; format++) {
    if (*format == '%') {
      width_left = 0;
      precision = 0;
      width_right = 0;
      format++;
      while (*format != '.' && isdigit((unsigned char)*format)) {
        width_left = width_left * 10 + (*format - '0');
        format++;
      }
      if (*format == '+') {
        *str++ = '+';
        count++;
        format++;
      } else if (*format == ' ') {
        *str++ = ' ';
        count++;
        format++;
      } else if (*format == '-') {
        format++;
        while (isdigit(*format)) {
          width_right = width_right * 10 + (*format - '0');
          format++;
        }
      }
      format = precision_str(format, &precision);
      format = length_str(format, &length);
      format = spec_check(format, args, &str, &length, &precision, &count,
                          width_right, width_left);
    } else {
      *str = *format;
      count++;
      str++;
    }
  }
  *str = '\0';
  va_end(args);
  return count;
}