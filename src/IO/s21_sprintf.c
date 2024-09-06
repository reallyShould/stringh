#include "../s21_string.h"

void spase_after_or_before(
    int *width, int *count, char **str,
    char *spase) {  // пробелы после текста и выравнивание слева
  if (*width > 0) {
    while (*width > 0) {
      (*count)++;
      **str = *spase;
      (*str)++;
      (*width)--;
    }
  }
}

void spase_int(int *width, int *count, char **str, char *spase, int *len,
               int *width_right) {  // пробелы после текста и выравнивание слева
  if (*width > 0) {
    while (*width > 0) {
      (*count)++;
      (*str)[(*len)++] = *spase;
      (*width)--;
      if (*width_right > 0) (*width_right)--;
    }
  }
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

const char *precision_format(const char *format, int *precision,
                             char spase[][6]) {
  if (*format == '.') {
    (*spase)[3] = '1';
    format++;
    if (*format == '0' && !(isdigit(*(format + 1)))) {
      *precision = -1;
      format++;
    } else if (isdigit((unsigned char)*format)) {
      while (isdigit((unsigned char)*format)) {
        *precision = *precision * 10 + (*format - '0');
        format++;
      }
    } else {
      *precision = -1;
    }
  }
  return format;
}

void letter_cpy(char **str, int *letter, int *width_right, int *width_left,
                int *count, char *spase) {
  if (*width_left && *letter != 0) (*width_left)--;
  *spase = ' ';

  spase_after_or_before(width_left, count, str,
                        spase);  // пробелы перед текстом и выравнивание справа

  **str = *letter;
  (*str)++;
  (*count)++;
  if (*width_right) (*width_right)--;
  spase_after_or_before(width_right, count, str,
                        spase);  // пробелы после текста и выравнивание слева
}

void str_cpy(char **str, char **string, int *width_right, int *width_left,
             int *count, char *spase, int *precision) {
  int len_str = s21_strlen((*string));
  if (spase[3] == '1') {  // Если был флаг '.'
    if (*width_left > *precision && *precision > 0)
      *width_left -= *precision;
    else if (*precision > 0) {
      if (*precision > *width_left && *width_left > len_str)
        *width_left -= len_str;
      else if (*precision > 0)
        *width_left = 0;
    }
    if (*precision > *width_right) {
      *width_right = 0;
    }
  } else {  // Если не было флага '.'
    // ситуация, когда длина больше счётчик записыннах символов и размер
    // записываемойстроки
    if ((((*count) + (len_str)) < *width_left) && len_str > 0)
      *width_left -= (len_str + (*count));
    else if (len_str > 0)
      *width_left = 0;
  }

  spase_after_or_before(width_left, count, str,
                        spase);  // пробелы перед текстом и выравнивание справа

  if (spase[3] == '0' || *precision > 0) {
    while (**string != '\0') {
      **str = **string;
      (*str)++;
      (*string)++;
      (*count)++;
      if (*width_right) (*width_right)--;
      if (*precision > 1)
        (*precision)--;
      else if (spase[3] == '1')
        break;
    }
  }
  spase_after_or_before(width_right, count, str, spase);
}
int long_int_to_str(long int num, char **str, int *count, int *width_right,
                    int width_left, char *spase, int *precision) {
  int len = 0;
  int negative = 0;
  if (num < 0L) {
    negative = 1;
    num = -num;
    if (*width_right > 0) (*width_right)--;  // Счётчик пробелов после текста
    if (width_left > 0) (width_left)--;  // Счётчик для пробелов после текста
    (*count)++;
    if (spase[1] == '1') spase[1] = '0';
  }

  do {
    (*str)[len++] = '0' + (int)(num % 10L);
    num /= 10L;
    (*count)++;  // Счётчик количества записей в str
    if (*width_right > 0)
      (*width_right)--;  // Счётчик для пробелов после текста
    if (width_left > 0) (width_left)--;  // Счётчик для пробелов после текста
    if (*precision > 0) (*precision)--;
  } while (num != 0L);

  if (spase[3] == '0' && spase[0] == '0' && width_left > 0) {
    *precision = width_left;
    width_left = 0;
    if (spase[1] == '1') {
      (*precision)--;

    } else if (spase[4] == '1' && negative == 0)
      (*precision)--;
  }
  if (width_left >= *precision && *precision > 0)
    width_left -= (*precision);
  else if (*precision > width_left && width_left > 0)
    width_left -= (*precision);

  if (*spase == ' ' && (*precision) > 0) *spase = '0';
  if (*spase == '0') spase_int(precision, count, str, spase, &len, width_right);

  if (negative == 1) {
    (*str)[len++] = '-';
  } else {
    if (spase[1] == '1') {
      (*str)[len++] = '+';
      if (spase[1] == '1') {
        (*count)++;
        if (width_left > 0) (width_left)--;
        if (*width_right > 0) (*width_right)--;
      }
    } else if (spase[4] == '1' && width_left < 2) {
      (*str)[len++] = ' ';
      (*count)++;
      if (width_left > 0) width_left--;
      if (*width_right > 0) (*width_right)--;
    }
  }
  if (width_left > 0) *spase = ' ';

  if (*spase == ' ')
    spase_int(&width_left, count, str, spase, &len, width_right);

  for (int i = 0; i < len / 2; i++) {
    char temp = (*str)[i];
    (*str)[i] = (*str)[len - i - 1];
    (*str)[len - i - 1] = temp;
  }
  return len;
}

int short_int_to_str(short int num, char **str, int *count, int *width_right,
                     int width_left, char *spase, int *precision) {
  int len = 0;
  int negative = 0;
  if (num < 0) {
    negative = 1;
    num = -num;
    if (*width_right > 0) (*width_right)--;  // Счётчик пробелов после текста
    if (width_left > 0) (width_left)--;  // Счётчик для пробелов после текста
    (*count)++;
    if (spase[1] == '1') spase[1] = '0';
  }

  do {
    (*str)[len++] = '0' + num % 10;
    num /= 10;
    (*count)++;  // Счётчик количества записей в str
    if (*width_right > 0)
      (*width_right)--;  // Счётчик для пробелов после текста
    if (width_left > 0) (width_left)--;  // Счётчик для пробелов после текста
    if (*precision > 0) (*precision)--;
  } while (num != 0);

  if (spase[3] == '0' && spase[0] == '0' && width_left > 0) {
    *precision = width_left;
    width_left = 0;
    if (spase[1] == '1') {
      (*precision)--;

    } else if (spase[4] == '1' && negative == 0)
      (*precision)--;
  }
  if (width_left >= *precision && *precision > 0)
    width_left -= (*precision);
  else if (*precision > width_left && width_left > 0)
    width_left -= (*precision);

  if (*spase == ' ' && (*precision) > 0) *spase = '0';
  if (*spase == '0') spase_int(precision, count, str, spase, &len, width_right);

  if (negative == 1) {
    (*str)[len++] = '-';
  } else {
    if (spase[1] == '1') {
      (*str)[len++] = '+';
      if (spase[1] == '1') {
        (*count)++;
        if (width_left > 0) (width_left)--;
        if (*width_right > 0) (*width_right)--;
      }
    } else if (spase[4] == '1' && width_left < 2) {
      (*str)[len++] = ' ';
      (*count)++;
      if (width_left > 0) width_left--;
      if (*width_right > 0) (*width_right)--;
    }
  }

  if (width_left > 0) *spase = ' ';
  if (*spase == ' ')
    spase_int(&width_left, count, str, spase, &len, width_right);

  for (int i = 0; i < len / 2; i++) {
    char temp = (*str)[i];
    (*str)[i] = (*str)[len - i - 1];
    (*str)[len - i - 1] = temp;
  }
  return len;
}

int count_digits(int num) {
  int count = 0;
  while (num != 0) {
    num /= 10;
    count++;
  }
  return count;
}

int int_to_str(int num, char **str, int *count, int *width_right,
               int width_left, char *spase, int *precision) {
  int len = 0;
  int negative = 0;
  long int long_num = 0L;

  int num_count = count_digits(num);
  if (num_count >= 10) {
    long_num = (long int)num;
    len = long_int_to_str(long_num, str, count, width_right, width_left, spase,
                          precision);
  } else {
    if (num < 0) {
      negative = 1;
      num = -num;
      if (*width_right > 0) (*width_right)--;  // Счётчик пробелов после текста
      if (width_left > 0) (width_left)--;  // Счётчик для пробелов после текста
      (*count)++;
      if (spase[1] == '1') spase[1] = '0';
    }

    do {
      (*str)[len++] = '0' + num % 10;
      num /= 10;
      (*count)++;  // Счётчик количества записей в str
      if (*width_right > 0)
        (*width_right)--;  // Счётчик для пробелов после текста
      if (width_left > 0) (width_left)--;  // Счётчик для пробелов после текста
      if (*precision > 0) (*precision)--;
    } while (num != 0);

    if (spase[3] == '0' && spase[0] == '0' && width_left > 0) {
      *precision = width_left;
      width_left = 0;
      if (spase[1] == '1') {
        (*precision)--;
      } else if (spase[4] == '1' && negative == 0)
        (*precision)--;
    }
    if (width_left >= *precision && *precision > 0)
      width_left -= (*precision);
    else if (*precision > width_left && width_left > 0)
      width_left -= (*precision);

    if (*spase == ' ' && (*precision) > 0) *spase = '0';
    if (*spase == '0')
      spase_int(precision, count, str, spase, &len, width_right);

    if (negative == 1) {
      (*str)[len++] = '-';
    } else {
      if (spase[1] == '1') {
        (*str)[len++] = '+';
        if (spase[1] == '1') {
          (*count)++;
          if (width_left > 0) (width_left)--;
          if (*width_right > 0) (*width_right)--;
        }
      } else if (spase[4] == '1' && width_left < 2) {
        (*str)[len++] = ' ';
        (*count)++;
        if (width_left > 0) width_left--;
        if (*width_right > 0) (*width_right)--;
      }
    }

    if (width_left > 0) *spase = ' ';
    if (*spase == ' ')
      spase_int(&width_left, count, str, spase, &len, width_right);

    for (int i = 0; i < len / 2; i++) {
      char temp = (*str)[i];
      (*str)[i] = (*str)[len - i - 1];
      (*str)[len - i - 1] = temp;
    }
  }
  return len;
}

int long_int_u_to_str(unsigned long int num, char **str, int *count,
                      int *width_right, int width_left, char *spase,
                      int *precision) {
  int len = 0;
  do {
    (*str)[len++] = '0' + num % 10;
    num /= 10;
    (*count)++;  // Счётчик количества записей в str
    if (*width_right > 0)
      (*width_right)--;  // Счётчик для пробелов после текста
    if (width_left > 0) (width_left)--;  // Счётчик для пробелов после текста
    if (*precision > 0) (*precision)--;
  } while (num != 0);

  if (spase[3] == '0' && spase[0] == '0' && width_left > 0) {
    *precision = width_left;
    width_left = 0;
    if (spase[1] == '1') {
      (*precision)--;
    } else if (spase[4] == '1')
      (*precision)--;
  }
  if (width_left >= *precision && *precision > 0)
    width_left -= (*precision);
  else if (*precision > width_left && width_left > 0)
    width_left -= (*precision);

  if (*spase == ' ' && (*precision) > 0) *spase = '0';
  if (*spase == '0') spase_int(precision, count, str, spase, &len, width_right);

  if (width_left > 0) *spase = ' ';
  if (*spase == ' ')
    spase_int(&width_left, count, str, spase, &len, width_right);

  for (int i = 0; i < len / 2; i++) {
    char temp = (*str)[i];
    (*str)[i] = (*str)[len - i - 1];
    (*str)[len - i - 1] = temp;
  }
  return len;
}

int short_int_u_to_str(unsigned int num, char **str, int *count,
                       int *width_right, int width_left, char *spase,
                       int *precision) {
  int len = 0;
  do {
    (*str)[len++] = '0' + num % 10;
    num /= 10;
    (*count)++;  // Счётчик количества записей в str
    if (*width_right > 0)
      (*width_right)--;  // Счётчик для пробелов после текста
    if (width_left > 0) (width_left)--;  // Счётчик для пробелов после текста
    if (*precision > 0) (*precision)--;
  } while (num != 0);

  if (spase[3] == '0' && spase[0] == '0' && width_left > 0) {
    *precision = width_left;
    width_left = 0;
    if (spase[1] == '1') {
      (*precision)--;
    } else if (spase[4] == '1')
      (*precision)--;
  }
  if (width_left >= *precision && *precision > 0)
    width_left -= (*precision);
  else if (*precision > width_left && width_left > 0)
    width_left -= (*precision);

  if (*spase == ' ' && (*precision) > 0) *spase = '0';
  if (*spase == '0') spase_int(precision, count, str, spase, &len, width_right);

  if (width_left > 0) *spase = ' ';
  if (*spase == ' ')
    spase_int(&width_left, count, str, spase, &len, width_right);

  for (int i = 0; i < len / 2; i++) {
    char temp = (*str)[i];
    (*str)[i] = (*str)[len - i - 1];
    (*str)[len - i - 1] = temp;
  }
  return len;
}

int count_digits_u(unsigned num) {
  int count = 0;
  while (num != 0) {
    num /= 10;
    count++;
  }
  return count;
}

int int_u(unsigned int num, char **str, int *count, int *width_right,
          int width_left, char *spase, int *precision) {
  int len = 0;
  unsigned long int long_num = 0L;
  int num_count = count_digits_u(num);
  if (num_count >= 10) {
    long_num = (unsigned long int)num;
    len = long_int_u_to_str(long_num, str, count, width_right, width_left,
                            spase, precision);
  } else {
    do {
      (*str)[len++] = '0' + num % 10;
      num /= 10;
      (*count)++;  // Счётчик количества записей в str
      if (*width_right > 0)
        (*width_right)--;  // Счётчик для пробелов после текста
      if (width_left > 0) (width_left)--;  // Счётчик для пробелов после текста
      if (*precision > 0) (*precision)--;
    } while (num != 0);

    if (spase[3] == '0' && spase[0] == '0' && width_left > 0) {
      *precision = width_left;
      width_left = 0;
      if (spase[1] == '1') {
        (*precision)--;
      }
    }
    if (width_left >= *precision && *precision > 0)
      width_left -= (*precision);
    else if (*precision > width_left && width_left > 0)
      width_left -= (*precision);

    if (*spase == ' ' && (*precision) > 0) *spase = '0';
    if (*spase == '0')
      spase_int(precision, count, str, spase, &len, width_right);

    if (width_left > 0) *spase = ' ';
    if (*spase == ' ')
      spase_int(&width_left, count, str, spase, &len, width_right);

    for (int i = 0; i < len / 2; i++) {
      char temp = (*str)[i];
      (*str)[i] = (*str)[len - i - 1];
      (*str)[len - i - 1] = temp;
    }
  }
  return len;
}

void space_to_float(float num, char **str, int *precision, int *count,
                    int *width_left, char *spase) {
  if (*width_left) {  // Ветка для пробелов перед текстом
    int WholePart1 = (int)num;
    double decimalPart1 = num - WholePart1;
    int precision1 = *precision;

    if (precision1 == -1) WholePart1 += round(decimalPart1);

    while (WholePart1 != 0 && *width_left) {
      (*width_left)--;  // Счётчик для пробелов перед текстом
      WholePart1 /= 10;
    }
    if (precision1 > -1 && *width_left) {
      (*width_left)--;
      if (*width_left) {  // Счётчик для пробелов перед текстом
        if (precision1 > 0) {
          long long digit = 1;
          while (precision1 > 0 && *width_left) {
            digit *= 10;  // пока ширина не кончится, умножаем число на 10
            precision1--;
            (*width_left)--;  // Счётчик для пробелов после текста
          }
        } else {
          int digit = 1;
          int count_after_point = 0;
          while (count_after_point != 6 && *width_left) {
            digit *= 10;  // пока ширина не кончится, умножаем число на 10
            (*width_left)--;  // Счётчик для пробелов после текста
            count_after_point++;
          }
        }
      }
    }
    if ((*width_left > 0 && spase[1] == '1' && *spase == ' ') ||
        (*width_left > 1 && spase[4] == '1' && num > 0))
      (*width_left)--;
    spase_after_or_before(
        width_left, count, str,
        spase);  // пробелы перед текстом и выравнивание справа
  }
}

char *float_to_str(double num, char **str, int *precision, int *count,
                   int *width_right, int width_left, char *spase) {
  int len = 0, negative = 0, WholePart = 0;
  if (num < 0) {
    negative = 1;
    num = -num;
    (*count)++;  // Счётчик количества записей в str
    if (width_left) width_left--;  // Счётчик для пробелов перед текстом
    if (*width_right) (*width_right)--;  // Счётчик для пробелов после текста
    if (spase[1] == '1') spase[1] = '0';
  }
  WholePart = (int)num;
  double decimalPart = num - WholePart;
  if (*precision == -1) WholePart += round(decimalPart);
  if (*spase == ' ')
    space_to_float(num, str, precision, count, &width_left, spase);
  if (negative == 1) {
    (**str) = '-';
    (*str)++;
  } else {
    if (spase[1] == '1') {
      (**str) = '+';
      (*str)++;
      (*count)++;
      if (width_left > 0 && spase[1] == '1') (width_left)--;
      if (*width_right > 0 && spase[1] == '1') (*width_right)--;
    } else if (spase[4] == '1') {
      (**str) = ' ';
      (*str)++;
      (*count)++;
      if (*width_right) (*width_right)--;
    }
  }
  if (*spase == '0')
    space_to_float(num, str, precision, count, &width_left, spase);

  char *buffer = malloc(200 * sizeof(char));
  int index = 0;
  do {
    buffer[index++] = '0' + WholePart % 10;
    WholePart /= 10;
  } while (WholePart != 0);

  for (int i = index - 1; i >= 0; i--) {
    (*str)[len++] = buffer[i];
    (*count)++;
    if (*width_right) (*width_right)--;
  }

  if (*precision > -1) {
    (*str)[len++] = '.';
    (*count)++;
    if (*width_right) (*width_right)--;  // Счётчик для пробелов перед текстом
    if (*precision > 0) {
      long long digit = 1;
      int count_after_point = 0;
      while (*precision > 0) {
        digit *= 10;  // пока ширина не кончится, умножаем число на 10
        (*precision)--;
        if (*width_right)
          (*width_right)--;  // Счётчик для пробелов после текста
        (*count)++;  // Счётчик количества записей в str
        count_after_point++;
      }
      decimalPart *= digit;  // Умножаем дробь (0.n (где n - любое количество
                             // цифр после точки)) на получившееся число.
                             // Возможно нужно сделать явное приведения типов
      decimalPart = round(decimalPart);
      while (count_after_point > 0) {
        digit /= 10;  // шаг по цифре в переменной decimalPart
        (*str)[len++] = '0' + (long long int)decimalPart / digit % 10;
        count_after_point--;
      }
    } else {
      while (len < 8) {
        int digit = 1;
        int count_after_point = 0;
        while (count_after_point != 6) {
          digit *= 10;  // пока ширина не кончится, умножаем число на 10
          if (*width_right)
            (*width_right)--;  // Счётчик для пробелов после текста
          (*count)++;  // Счётчик количества записей в str
          count_after_point++;
        }
        decimalPart *= digit;  // Умножаем дробь (0.n (где n - любое количество
                               // цифр после точки)) на получившееся число.
                               // Возможно нужно сделать явное приведения типов
        decimalPart = round(decimalPart);
        while (count_after_point > 0) {
          digit /= 10;  // шаг по цифре в переменной decimalPart
          (*str)[len++] = '0' + (int)decimalPart / digit % 10;
          count_after_point--;
        }
      }
    }
  }
  for (int i = 0; i < len; ++i)
    (*str)++;  // Шагает по строке, что бы вернуть адрес
  free(buffer);
  return (*str);
}

char *spec_d(char **str, va_list args, int *length, int *count,
             int *width_right, int width_left, char *spase, int *precision) {
  int len = 0;
  if (spase[3] == '1') spase[0] = '0';

  if (*length == 1) {
    long int num_l = va_arg(args, long int);
    len = long_int_to_str(num_l, str, count, width_right, width_left, spase,
                          precision);
    do {
      (*str)++;
      len--;
    } while (len > 0);
  } else if (*length == -1) {
    short int num_h = va_arg(args, int);
    len = short_int_to_str(num_h, str, count, width_right, width_left, spase,
                           precision);
    do {
      (*str)++;
      len--;
    } while (len > 0);
  } else {
    int num = va_arg(args, int);
    len =
        int_to_str(num, str, count, width_right, width_left, spase, precision);
    do {
      (*str)++;
      len--;
    } while (len > 0);
  }
  return *str;
}

char *spec_u(char **str, va_list args, int *length, int *count,
             int *width_right, int width_left, char *spase, int *precision) {
  int len = 0;
  if (spase[3] == '1') spase[0] = '0';
  if (spase[1] == '1') spase[1] = '0';
  if (spase[4] == '1') spase[4] = '0';
  if (*length == 1) {
    unsigned long int num_l = va_arg(args, unsigned long int);
    len = long_int_u_to_str(num_l, str, count, width_right, width_left, spase,
                            precision);
    do {
      (*str)++;
      len--;
    } while (len > 0);
  } else if (*length == -1) {
    unsigned short int num_h = va_arg(args, unsigned int);
    len = short_int_u_to_str(num_h, str, count, width_right, width_left, spase,
                             precision);
    do {
      (*str)++;
      len--;
    } while (len > 0);
  } else {
    unsigned int num_u = va_arg(args, unsigned int);
    len = int_u(num_u, str, count, width_right, width_left, spase, precision);
    do {
      (*str)++;
      len--;
    } while (len > 0);
  }
  return *str;
}

const char *spec_check(const char *format, va_list args, char **str,
                       int *length, int *precision, int *count, int width_right,
                       int width_left, char *spase) {
  switch (*format) {
    case 'c': {
      int letter = va_arg(args, int);
      letter_cpy(str, &letter, &width_right, &width_left, count, spase);
      break;
    }
    case 'd': {
      *str = spec_d(str, args, length, count, &width_right, width_left, spase,
                    precision);  // Функция возвращает количество шагов в строку
      *spase = ' ';

      spase_after_or_before(
          &width_right, count, str,
          spase);  // пробелы после текста и выравнивание слева
      break;
    }
    case 'f': {
      double float_num = va_arg(args, double);
      *str = float_to_str(float_num, str, precision, count, &width_right,
                          width_left, spase);
      *spase = ' ';
      spase_after_or_before(
          &width_right, count, str,
          spase);  // пробелы после текста и выравнивание слева
      break;
    }
    case 'u': {
      if (spase[1] == '1') spase[1] = '0';
      *str = spec_u(str, args, length, count, &width_right, width_left, spase,
                    precision);
      *spase = ' ';
      spase_after_or_before(
          &width_right, count, str,
          spase);  // пробелы после текста и выравнивание слева
      break;
    }
    case 's': {  // %s для тебя, %с и %f сделаны, я делаю %d, %u
      if (spase[0] == '0') spase[0] = ' ';
      char *string = va_arg(args, char *);
      str_cpy(str, &string, &width_right, &width_left, count, spase, precision);
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

const char *search_flags(char spase[][6], const char *format) {
  if (*format == '0' && (*spase)[0] == ' ') {
    (*spase)[0] = '0';
  } else if (*format == '+' && (*spase)[1] == '0') {
    (*spase)[1] = '1';
  } else if (*format == '-' && (*spase)[2] == '0') {
    (*spase)[2] = '1';
  } else if (isspace(*format) && (*spase)[4] == '0') {
    (*spase)[4] = '1';
  }
  format++;
  return format;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int width_left = 0;  // ширина перед текстом (%20d)
  int precision = 0;   // Ширина после точки (%.20d)
  int width_right = 0;  // ширина после теста текстом (%-20d)
  int length = 0;       // длинна (%ld)
  int count = 0;  // счётчик записи символов в строку
  for (; *format != '\0'; format++) {
    if (*format == '%') {
      char spase[] = " 0000";  // массив для хранения флагов
      width_left = 0;
      precision = 0;
      width_right = 0;
      format++;
      while (isspace(*format) || *format == '+' || *format == '-' ||
             *format == '0')
        format =
            search_flags(&spase, format);  // Парсер флагов (пробел, -, +, 0)
      if (spase[1] == '1') spase[4] = '0';  // Взаимоисключающая ситуация
      if (spase[2] == '1') spase[0] = ' ';  // Взаимоисключающая ситуация
      if (isdigit(*format)) {
        if (spase[2] == '1') {
          while (isdigit((unsigned char)*format)) {  // Парсер для ширина после
                                                     // теста (%-20d)
            width_right = width_right * 10 + (*format - '0');
            format++;
          }
          // printf("%d\n", width_right);
        }
        if (spase[2] == '0') {
          while (isdigit((unsigned char)*format)) {  // Парсер для ширины перед
                                                     // текстом (%20d)
            width_left = width_left * 10 + (*format - '0');
            format++;
          }
          // printf("%d\n", width_left);
        }
      }
      format = precision_format(format, &precision,
                                &spase);  // Парсер для после точки (%.20d)
      format = length_str(format, &length);  // Парсер для длины (%ld)
      format = spec_check(format, args, &str, &length, &precision,
                          &count,  // парсер спецификаторов
                          width_right, width_left, spase);
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