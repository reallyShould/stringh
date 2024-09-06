#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

#include "../s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int result = 0, back = 0, length = 0, width = 0;
  const char *p = format, *start = str;  // *start Для %n
  if (!(*str))
    result--;
  else {
    for (int i = 0; isspace(str[i]) && str[i] != '\0'; ++i) {
      if (str[i + 1] == '\0') {
        result--;
        back = 2;
      }
    }
  }
  while (*p && (*str) && back != 2) {
    back = 0, length = 0,
    width = -1;  // Сброс счётчиков завершения работы, длины и ширины
    if (isspace(*p))  // для пропуска пробелов, если перед %c есть пробел
      while (isspace(*str)) str++;
    while (isspace(*p))
      p++;  // Пропуск пробелов перед спецификаторами, если они есть
    if (*p == '%' && *(p + 1)) {
      p++;
      if (*p == '*') {  // Если в строке формата после % идёт *
        back = read_but_not_wright(&str, &p, length, &width);
        continue;
      }
      width = parsing_width(&p);  // Парсинг ширины, указанной в строке формата
      length = parsing_length(&p);  // Парсинг длины, указанной в строке формата
      if (back != 2) {  //Прасинг спецификаторов
        back = read_and_wright(args, &str, &result, &p, length, width, start,
                               back);
        if (back == 6) continue;
        p++;
        if (back == 2) break;
      }
    } else {
      if (*p == *str) {
        p++;
        str++;
      } else
        back = 2;
    }
  }
  while (*p && *p != '%') p++;
  if (*p == '%' && *(p + 1) == 'n') {
    p++;
    read_and_wright(args, &str, &result, &p, length, width, start, back);
  }
  va_end(args);
  return result;
}

int read_and_wright(va_list args, const char **str, int *result, const char **p,
                    int length, int width, const char *start, int back) {
  if (**p == 's') {  // Парсинг спецификатора в строке формата
    void *sp = s21_NULL;
    sp = va_arg((args), void *);
    if ((back = s_specifier(sp, str, result, &width))) va_end(args);
  } else if (**p == 'c') {
    void *cp = s21_NULL;
    cp = va_arg(args, void *);
    *(int *)cp = 0;
    if ((back = c_specifier(cp, str, result, &width))) va_end(args);
  } else if (**p == 'd') {
    void *dp = s21_NULL;
    dp = va_arg((args), void *);
    back = d_specifier(dp, str, result, length, &width);
  } else if (**p == 'u') {
    void *up = s21_NULL;
    up = va_arg(args, void *);
    if ((back = u_specifier(up, str, result, length, &width))) va_end(args);
  } else if (**p == 'i') {
    void *ip = s21_NULL;
    ip = va_arg(args, void *);
    back = i_specifier(str);
    if (back == 3) {
      back = x_specifier(ip, str, result, length, &width);
    } else if (back == 4) {
      back = o_specifier(ip, str, result, length, &width);
    } else if (back == 5) {
      back = d_specifier(ip, str, result, length, &width);
    } else if (back == 2)
      va_end(args);
  } else if (**p == 'x' || **p == 'X' || **p == 'p') {
    if (**p == 'p') length = 1;
    void *xp = s21_NULL;
    xp = va_arg(args, void *);
    if ((back = x_specifier(xp, str, result, length, &width))) va_end(args);
  } else if (**p == 'o') {
    void *op = s21_NULL;
    op = va_arg(args, void *);
    if ((back = o_specifier(op, str, result, length, &width))) va_end(args);
  } else if (**p == 'n') {
    void *np = s21_NULL;
    np = va_arg(args, void *);
    *(int *)np = 0;
    start = n_specifier(np, str, start);
  } else if (**p == 'f' || **p == 'e' || **p == 'E' || **p == 'g' ||
             **p == 'G') {
    void *fp = s21_NULL;
    fp = va_arg(args, void *);
    if ((back = f_specifier(fp, str, result, length, &width))) va_end(args);
  } else if ((**str == **p)) {
    (*p)++, (*str)++, back = 6;
  } else
    back = 2;
  return back;
}

int read_but_not_wright(const char **str, const char **p, int length,
                        int *width) {
  int back = 0;
  int result1 = 0;
  if (*(*p + 1) != 'c') {
    while (isspace(**str)) (*str)++;
    while (!isspace(**str)) {
      if (*(*p + 1) == 'x' || *(*p + 1) == 'X' || *(*p + 1) == 'p') {
        int digit = 0;
        if (*(*p + 1) == 'p') length = 1;
        back = x_specifier((void *)&digit, str, &result1, length,
                           width);  // Считывает, но не записывает в va_arg
        break;
      } else if (*(*p + 1) == 'o') {
        int digit = 0;
        back = o_specifier((void *)&digit, str, &result1, length, width);
        break;
      } else if (*(*p + 1) == 'd' || *(*p + 1) == 'u') {
        int digit = 0;
        back = d_specifier((void *)&digit, str, &result1, length, width);
        break;
      } else if (*(*p + 1) == 'f' || *(*p + 1) == 'e' || *(*p + 1) == 'E' ||
                 *(*p + 1) == 'g' || *(*p + 1) == 'G') {
        float digit = 0;
        back = f_specifier((void *)&digit, str, &result1, length, width);
        break;
      } else if (*(*p + 1) == 's') {
        char str2[1000000] = {0};
        back = s_specifier((void *)&str2, str, &result1, width);
        break;
      } else if (*(*p + 1) == 'i') {
        int digit = 0;
        back = i_specifier(str);
        if (back == 3)
          back = x_specifier((void *)&digit, str, &result1, length, width);
        else if (back == 4)
          back = o_specifier((void *)&digit, str, &result1, length, width);
        else if (back == 5)
          back = d_specifier((void *)&digit, str, &result1, length, width);
        break;
      }
    }
  } else if (*(*p + 1) == 'c')
    if (**str != '\0') (*str)++;
  while (!isspace(**p) && **p != '%')
    (*p)++;  // Пропуск читаемой строки формата до первого пробельного символа
  return back;
}

int parsing_width(const char **p) {
  int width = -1;
  if (isdigit(**p)) {
    width = 0;
    while (isdigit(**p)) {
      width = width * 10 + (*(*p) - '0');
      (*p)++;
    }
  }
  return width;
}

int parsing_length(const char **p) {
  int length = 0;
  if (**p == 'l' && length < 1) {
    length = 1;
    (*p)++;
  } else if (**p == 'h' && length > -1) {
    length = -1;
    (*p)++;
  } else if (**p == 'L' && length < 1) {
    length = 2;
    (*p)++;
  }
  return length;
}

int s_specifier(void *sp, const char **str, int *result, int *width) {
  int back = 0;
  while (isspace(**str)) (*str)++;  // Пропуск пробелов перед читаемой строкой
  if (**str == '\0')
    back = 2;
  else {
    while (**str && !isspace(**str) && *width != 0) {
      *(char *)sp++ = *(*str)++;
      (*width)--;
    }
    *(char *)sp = '\0';
    (*result)++;
  }
  return back;
}

int c_specifier(void *cp, const char **str, int *result, int *width) {
  int back = 0;
  if (**str == '\0')
    back = 2;
  else {
    *(char *)cp = **str;
    if ((*width) > 0) {
      // int backup = *width;
      while ((*width) > 0 && **str != '\0') {
        (*str)++;
        (*width)--;
      }
      // if(**str == '\0')
      // while(**str != *(char *)cp) str--;
    } else {
      (*str)++;
      (*width)--;
    }
    (*result)++;
  }
  return back;
}

int d_specifier(void *dp, const char **str, int *result, int length,
                int *width) {
  int sign = 1, back = 0;
  while (isspace(**str)) (*str)++;  // Пропуск пробелов перед читаемой строкой
  sign = skip_math_sign(
      str, width,
      sign);  // Проверка на положительное или отрицательное числов в строке
  if (!isdigit(**str) || !(*width))
    back = 2;
  else {
    if (length == 0) {  // Обработка длины
      int digit = 0;
      while (isdigit(**str) &&
             (*width)) {  // Цикл считывания из строки и обработка ширины
        digit = digit * 10 + (**str - '0');
        (*str)++;
        (*width)--;
      }
      // Тернарная условная операция подстановки с инвертированим всех бит
      // переменной, если sign != 1 (если digit был = 5 , digit становится = -6)
      *(int *)dp = 0;
      *(int *)dp = (sign == 1) ? digit : ~digit + 1;
    } else if (length == 1) {
      long int l_digit = 0L;
      while (isdigit(**str) && (*width)) {
        l_digit = l_digit * 10 + (**str - '0');
        (*str)++;
        (*width)--;
      }
      *(long int *)dp = 0L;
      *(long int *)dp = (sign == 1) ? l_digit : ~l_digit + 1;
    } else if (length == -1) {
      short int h_digit = 0;
      while (isdigit(**str) && (*width)) {
        h_digit = h_digit * 10 + (**str - '0');
        (*str)++;
        (*width)--;
      }
      *(short int *)dp = 0;
      *(short int *)dp = (sign == 1) ? h_digit : ~h_digit + 1;
    }
    if ((!isdigit(**str) && (**str != '+' && **str != '-')) &&
        !isspace(**str) && **str != '\0')
      back = 2;
    (*result)++;
  }
  return back;
}

int u_specifier(void *up, const char **str, int *result, int length,
                int *width) {
  unsigned sign = 1, back = 0;
  while (isspace(**str)) (*str)++;  // Пропуск пробелов перед читаемой строкой
  sign = (unsigned)skip_math_sign(str, width,
                                  sign);  // Проверка на знак числа в строке
  if (!isdigit(**str) || !(*width) || isspace(**str))
    back = 2;
  else {
    if (length == 0) {  // Обработка длины
      unsigned int digit = 0U;
      while (isdigit(**str) &&
             (*width)) {  // Цикл считывания из строки и обработка ширины
        digit = digit * 10 + (**str - '0');
        (*str)++;
        (*width)--;
      }
      // Тернарная условная операция подстановки с инвертированим всех бит
      // переменной, если sign != 1 (если digit был = 5 , digit становится = -6)
      *(unsigned int *)up = 0U;
      *(unsigned int *)up = (sign == (unsigned)1) ? digit : ~digit + 1;
    } else if (length == 1) {
      long unsigned int l_digit = 0UL;
      while (isdigit(**str) && (*width)) {
        l_digit = l_digit * 10 + (**str - '0');
        (*str)++;
        (*width)--;
      }
      *(long unsigned int *)up = 0UL;
      *(long unsigned int *)up = (sign == (unsigned)1) ? l_digit : ~l_digit + 1;
    } else if (length == -1) {
      short unsigned int h_digit = 0U;
      while (isdigit(**str) && (*width)) {
        h_digit = h_digit * 10 + (**str - '0');
        (*str)++;
        (*width)--;
      }
      *(short unsigned int *)up = 0U;
      *(short unsigned int *)up =
          (sign == (unsigned)1) ? h_digit : ~h_digit + 1;
    }
    if ((!isdigit(**str) && (**str != '+' && **str != '-')) &&
        !isspace(**str) && **str != '\0')
      back = 2;
    (*result)++;
  }
  return back;
}

int i_specifier(const char **str) {
  int back = 0, sign = 0, width1 = -1;
  char const *str_origin = *str;
  while (isspace(**str)) (*str)++;  // Пропуск пробелов перед читаемой строкой
  sign = skip_math_sign(str, &width1, sign);
  if (**str == '0') {
    (*str)++;
    if ((**str == 'x' || **str == 'X')) {  // Проверка на систему счислиния)
      back = 3;
    } else
      back = 4;
  } else if (isdigit(**str))
    back = 5;
  else
    back = 2;
  *str = str_origin;
  return back;
}

int x_specifier(void *xp, const char **str, int *result, int length,
                int *width) {
  int sign = 1, back = 0;
  while (isspace(**str)) (*str)++;  // Пропуск пробелов перед читаемой строкой
  sign = skip_math_sign(str, width,
                        sign);  // Проверка на знак числа в строке
  if ((!isxdigit(**str)) || !(*width))
    back = 2;
  else {
    if (**str == '0') {
      if ((*(*str + 1) == 'x' || *(*str + 1) == 'X') &&
          (*width) != 1) {  // Пропуск первых символов, если это формат
                            // шестнадцатеричного числа
        (*str) += 2;
        (*width) -= 2;
      } else {
        (*str)++;
        (*width)--;
      }
      if (!isxdigit(**str))  // Проверка на валидный символ
        if (**str != '-' && **str != '+' && !isspace(**str) && **str != '\0')
          back = 2;
    }
    if (back == 0 && (**str != '-' && **str != '+') && (*width)) {
      if (length == 0) {  // Обработка длины
        unsigned int digit = 0U;
        x_specifier_parser(&digit, str, width, &back);
        // Тернарная условная операция подстановки с инвертированим всех бит
        // переменной, если sign != 1 (если digit был = 5 , то digit = -6)
        *(unsigned int *)xp = 0U;
        *(unsigned int *)xp = (sign == 1) ? digit : ~digit + 1;
      } else if (length == 1) {
        unsigned long int digit = 0LU;
        lx_specifier_parser(&digit, str, width, &back);
        *(unsigned long int *)xp = 0LU;
        *(unsigned long int *)xp = (sign == 1) ? digit : ~digit + 1;
      } else if (length == -1) {
        unsigned short int digit = 0U;
        hx_specifier_parser(&digit, str, width, &back);
        *(unsigned short int *)xp = 0U;
        *(unsigned short int *)xp = (sign == 1) ? digit : ~digit + 1;
      }
    }
    (*result)++;
  }
  return back;
}

void x_specifier_parser(unsigned int *digit, const char **str, int *width,
                        int *back) {
  while (!isspace(**str) &&
         **str != '\0') {  // Цикл считывания из строки и обработка ширины
    if (isxdigit(*(*str + 1)) &&
        (*width) - 1 != 0) {  // Преобразование первого и последующих символов
                              // (кроме последнего)
      if (isdigit(**str)) {
        *digit |= (**str - '0');  // Добавление преобразованного символа
        *digit <<=
            4;  // Освобождение места под следующий шестнадцетиричный символ
      } else if (**str >= 'a' && **str <= 'f') {
        *digit |= (**str - 'a' + 10);
        *digit <<= 4;
      } else if (**str >= 'A' && **str <= 'F') {
        *digit |= (**str - 'A' + 10);
        *digit <<= 4;
      }
    } else {  // Преобразование последнего символа
      if (isdigit(**str)) {
        *digit |= (**str - '0');
      } else if (**str >= 'a' && **str <= 'f') {
        *digit |= (**str - 'a' + 10);
      } else if (**str >= 'A' && **str <= 'F') {
        *digit |= (**str - 'A' + 10);
      }
      (*width)--;
      (*str)++;
      if (!isxdigit(**str) &&
          !isspace(**str))  // Завершение работы програмы, если встретился
                            // невалидный символ
        if (**str != '+' && **str != '-' && (*width) && **str != '\0')
          *back = 2;
      break;
    }
    (*width)--;
    (*str)++;
  }
}

void lx_specifier_parser(unsigned long int *digit, const char **str, int *width,
                         int *back) {
  while (!isspace(**str) && **str != '\0' && **str != '\0') {
    if (isxdigit(*(*str + 1)) && (*width) - 1 != 0) {
      if (isdigit(**str)) {
        *digit |= (**str - '0');
        *digit <<= 4;
      } else if (**str >= 'a' && **str <= 'f') {
        *digit |= (**str - 'a' + 10);
        *digit <<= 4;
      } else if (**str >= 'A' && **str <= 'F') {
        *digit |= (**str - 'A' + 10);
        *digit <<= 4;
      }
    } else {
      if (isdigit(**str)) {
        *digit |= (**str - '0');
      } else if (**str >= 'a' && **str <= 'f') {
        *digit |= (**str - 'a' + 10);
      } else if (**str >= 'A' && **str <= 'F') {
        *digit |= (**str - 'A' + 10);
      }
      (*width)--;
      (*str)++;
      if (!isxdigit(**str) && !isspace(**str))
        if (**str != '+' && **str != '-' && **str != '\0') *back = 2;
      break;
    }
    (*width)--;
    (*str)++;
  }
}

void hx_specifier_parser(unsigned short int *digit, const char **str,
                         int *width, int *back) {
  while (!isspace(**str) && **str != '\0' && **str != '\0') {
    if (isxdigit(*(*str + 1)) && (*width) - 1 != 0) {
      if (isdigit(**str)) {
        *digit |= (**str - '0');
        *digit <<= 4;
      } else if (**str >= 'a' && **str <= 'f') {
        *digit |= (**str - 'a' + 10);
        *digit <<= 4;
      } else if (**str >= 'A' && **str <= 'F') {
        *digit |= (**str - 'A' + 10);
        *digit <<= 4;
      }
    } else {
      if (isdigit(**str)) {
        *digit |= (**str - '0');
      } else if (**str >= 'a' && **str <= 'f') {
        *digit |= (**str - 'a' + 10);
      } else if (**str >= 'A' && **str <= 'F') {
        *digit |= (**str - 'A' + 10);
      }
      (*width)--;
      (*str)++;
      if (!isxdigit(**str) && !isspace(**str))
        if (**str != '+' && **str != '-' && **str != '\0') *back = 2;
      break;
    }
    (*width)--;
    (*str)++;
  }
}

int o_specifier(void *op, const char **str, int *result, int length,
                int *width) {
  int sign = 1, back = 0;
  while (isspace(**str)) (*str)++;  // Пропуск пробелов перед читаемой строкой
  sign = skip_math_sign(
      str, width,
      sign);  // Проверка на положительное или отрицательное числов в строке
  if ((**str < '0' || **str > '7') || !(*width))
    back = 2;
  else {
    if (**str == '0' && (*width)) {  // пропуск идентификатора восьмир. символа
      (*str)++;
      (*width)--;
      if (**str < '0' || **str > '7')  // Проверка на валидный символ
        if (**str != '-' && **str != '+' && !isspace(**str) && **str != '\0')
          back = 2;
    }
    if (back == 0 && (*width)) {
      if (length == 0) {  // Обработка длины
        unsigned int digit = 0U;
        o_specifier_parser(&digit, str, width, &back);
        // Тернарная условная операция подстановки с инвертированим всех бит
        // переменной, если sign != 1 (если digit был = 5 , то digit = -6)
        *(unsigned int *)op = 0U;
        *(unsigned int *)op = (sign == 1) ? digit : ~digit + 1;
      } else if (length == 1) {
        unsigned long int l_digit = 0LU;
        lo_specifier_parser(&l_digit, str, width, &back);
        *(unsigned long int *)op = 0LU;
        *(unsigned long int *)op = (sign == 1) ? l_digit : ~l_digit + 1;
      } else if (length == -1) {
        unsigned short int h_digit = 0U;
        ho_specifier_parser(&h_digit, str, width, &back);
        *(unsigned short int *)op = 0U;
        *(unsigned short int *)op = (sign == 1) ? h_digit : ~h_digit + 1;
      }
    }
    (*result)++;
    if (((**str < '0' || **str > '7') && (**str != '+' && **str != '-')) &&
        !isspace(**str) && (*width) && **str != '\0')
      back = 2;
  }
  return back;
}

void o_specifier_parser(unsigned int *digit, const char **str, int *width,
                        int *back) {
  while (isdigit(**str) &&
         (*width)) {  // Цикл считывания из строки и обработка ширины
    if (((*(*str + 1)) >= '0' && (*(*str + 1)) <= '7') &&
        (*width) - 1 != 0) {  // Преобразование первого и последующих символов
                              // (кроме последнего)
      *digit |= (**str - '0');  // Добавление преобразованного символа
      *digit <<= 3;  // Освобождение места под следующий восьмеричный символ
    } else if (**str >= '0' && **str <= '7') {
      *digit |= (**str - '0');
      (*width)--;
      (*str)++;
      if ((**str < '0' || **str > '7') &&
          !isspace(**str))  // Завершение работы програмы, если встретился
                            // невалидный символ
        if (**str != '+' && **str != '-' && (*width) && **str != '\0')
          *back = 2;
      break;
    }
    (*width)--;
    (*str)++;
  }
}

void lo_specifier_parser(unsigned long int *digit, const char **str, int *width,
                         int *back) {
  while (isdigit(**str) && (*width)) {
    if (((*(*str + 1)) >= '0' && (*(*str + 1)) <= '7') && (*width) - 1 != 0) {
      if (**str >= '0' && **str < '8') {
        *digit |= (**str - '0');
        *digit <<= 3;
      }
    } else if (**str >= '0' && **str < '8') {
      *digit |= (**str - '0');
      (*width)--;
      (*str)++;
      if ((**str < '0' || **str > '7') && !isspace(**str))
        if (**str != '+' && **str != '-' && **str != '\0') *back = 2;
      break;
    }
    (*width)--;
    (*str)++;
  }
}

void ho_specifier_parser(unsigned short int *digit, const char **str,
                         int *width, int *back) {
  while (isdigit(**str) && (*width)) {
    if (((*(*str + 1)) >= '0' && (*(*str + 1)) <= '7') && (*width) - 1 != 0) {
      if (**str >= '0' && **str < '8') {
        *digit |= (**str - '0');
        *digit <<= 3;
      }
    } else if (**str >= '0' && **str < '8') {
      *digit |= (**str - '0');
      (*width)--;
      (*str)++;
      if ((**str < '0' || **str > '7') && !isspace(**str))
        if (**str != '+' && **str != '-' && **str != '\0') *back = 2;
      break;
    }
    (*width)--;
    (*str)++;
  }
}

const char *n_specifier(void *np, const char **str, const char *start) {
  int digit = 0;
  while ((*str) != start) {
    start++;
    digit++;
  }
  *(int *)np += digit;
  return start;
}

int f_specifier(void *fp, const char **str, int *result, int length,
                int *width) {
  int sign = 1, back = 0;
  while (isspace(**str)) (*str)++;  // Пропуск пробелов перед читаемой строкой
  sign = skip_math_sign(
      str, width,
      sign);  // Проверка на положительное или отрицательное числов в строке
  if ((((!isdigit(**str) && **str != '.') ||
        (**str == '.' && !((*width) - 1)))) ||
      (!isdigit(**str) && !isdigit(*(*str + 1)) && !isdigit(*(*str - 1))) ||
      !(*width)) {
    back = 2;
  } else if ((*width)) {
    if (length == 0) {  // Обработка длины
      float digit = 0.0;
      back = f_specifier_parser(&digit, str, width);
      *(float *)fp = 0.0;
      *(float *)fp = (sign == 1) ? digit : -digit;
    } else if (length == 2) {
      long double digit = 0.0L;
      back = Lf_specifier_parser(&digit, str, width);
      *(long double *)fp = 0.0L;
      *(long double *)fp = (sign == 1) ? digit : -digit;
    }
    if (back != 3)
      (*result)++;
    else
      back = 2;
    if ((!isdigit(**str) && (**str != '+' && **str != '-') && **str != '.') &&
        !isspace(**str) && **str != '\0')
      back = 2;
  }
  while (!isspace(**str) && (*width) != 0 &&
         (**str != '+' && **str != '-' && **str != '.') && !isdigit(**str) &&
         **str != '\0')
    (*str)++;  // Пропуск символов в строке до пробела, если они остались
  return back;
}

int f_specifier_parser(float *digit, const char **str, int *width) {
  int back = 0, count = 0;  // back-счётчик завершения, count - счётчик до '.'
  float digit_after_point = 1.0;
  while (isdigit(**str) && (*width)) {  // Чтение целочисленной части
    *digit = *digit * 10 + (**str - '0');
    (*str)++;
    (*width)--;
    count++;
  }
  if ((**str) == '.' && (*width)) {
    if (count == 0 && !isdigit(*(*str + 1))) back = 3;
    (*str)++;
    (*width)--;
    if (isdigit(**str) && (*width)) {
      while (isdigit(**str) &&
             (*width)) {  // Чтение дробной чтасти и обработка ширины
        *digit = *digit * 10 + (**str - '0');
        (*width)--;
        (*str)++;
        digit_after_point *= 10;
      }
      *digit /= digit_after_point;
    }
  } else if (!isdigit(*(*str + 1)) && !isdigit(*(*str + 2)) && (*width))
    if (!((**str == 'e' || **str == 'E') &&
          (*(*str + 1) == '+' || *(*str + 1) == '-') && *(*str + 2) == '.' &&
          isdigit(*(*str + 3))) &&
        **str != '\0') {
      back = 2;
    }
  if ((**str == 'e' || **str == 'E') && (*width) &&
      !back) {  // Обработка экспоненциальной формы числа в строке
    int e_sign = 1, e_digit = 0;
    (*str)++;
    (*width)--;
    e_sign = skip_math_sign(str, width, e_sign);
    if (isdigit(**str) && (*width)) {
      while (isdigit(**str) && (*width)) {
        e_digit = e_digit * 10 + (**str - '0');
        (*str)++;
        (*width)--;
      }
      digit_after_point = 1;
      for (int i = 1; i <= e_digit; ++i) digit_after_point *= 10;
      if (e_sign == 1)
        *digit *= digit_after_point;
      else
        *digit /= digit_after_point;
    }
  }
  return back;
}

int Lf_specifier_parser(long double *digit, const char **str, int *width) {
  int back = 0, count = 0;  // back - счётчик завершения, count - счётчик
                            // проверки, было ли число до **str == '.'
  long double digit_after_point = 1.0;
  while (isdigit(**str) && (*width)) {  // Чтение целочисленной части
    *digit = *digit * 10 + (**str - '0');
    (*str)++;
    (*width)--;
    count++;
  }
  if ((**str) == '.' && (*width)) {
    if (count == 0 && !isdigit(*(*str + 1))) back = 3;
    (*str)++;
    (*width)--;
    if (isdigit(**str) && (*width)) {
      while (isdigit(**str) &&
             (*width)) {  // Чтение дробной чтасти и обработка ширины
        *digit = *digit * 10 + (**str - '0');
        (*width)--;
        (*str)++;
        digit_after_point *= 10;
      }
      *digit /= digit_after_point;
    }
  } else if (!isdigit(*(*str + 1)) && !isdigit(*(*str + 2)) && (*width))
    if (!((**str == 'e' || **str == 'E') &&
          (*(*str + 1) == '+' || *(*str + 1) == '-') && *(*str + 2) == '.' &&
          isdigit(*(*str + 3))) &&
        **str != '\0')
      back = 2;
  if ((**str == 'e' || **str == 'E') && (*width) &&
      !back) {  // Обработка экспоненциальной формы числа в строке
    int e_sign = 1, e_digit = 0;
    (*str)++;
    (*width)--;
    e_sign = skip_math_sign(str, width, e_sign);
    if (isdigit(**str) && (*width)) {
      while (isdigit(**str) && (*width)) {
        e_digit = e_digit * 10 + (**str - '0');
        (*str)++;
        (*width)--;
      }
      digit_after_point = 1;
      for (int i = 1; i <= e_digit; ++i) digit_after_point *= 10;
      if (e_sign == 1)
        *digit *= digit_after_point;
      else
        *digit /= digit_after_point;
    }
  }
  return back;
}

int skip_math_sign(const char **str, int *width, int sign) {
  if ((*width) != 0) {
    if (**str == '-') {
      sign = -1;
      (*str)++;
      (*width)--;
    } else if (**str == '+') {
      sign = 1;
      (*str)++;
      (*width)--;
    }
  }
  return sign;
}