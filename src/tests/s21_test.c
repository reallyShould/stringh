#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(S21_MEMCHR) {
  char* res_21 = s21_memchr("Hello world!", 'o', strlen("Hello world!"));
  char* res_norm = memchr("Hello world!", 'o', strlen("Hello world!"));
  ck_assert_msg(res_21 == res_norm, "Fail (Hello world!, o)");
  res_21 = s21_memchr("Hello world!", '9', strlen("Hello world!"));
  res_norm = memchr("Hello world!", '9', strlen("Hello world!"));
  ck_assert_msg(res_21 == res_norm, "Fail (Hello world!, 9)");
  res_21 = s21_memchr("Hello world!", '!', strlen("Hello world!"));
  res_norm = memchr("Hello world!", '!', strlen("Hello world!"));
  ck_assert_msg(res_21 == res_norm, "Fail (Hello world!, !)");
  res_21 = s21_memchr("Hello world!", ' ', strlen("Hello world!"));
  res_norm = memchr("Hello world!", ' ', strlen("Hello world!"));
  ck_assert_msg(res_21 == res_norm,
                "Fail (Hello world!, "
                ")");
  res_21 = s21_memchr("", '!', strlen("Hello world!"));
  res_norm = memchr("", '!', strlen("Hello world!"));
  ck_assert_msg(res_21 == res_norm,
                "Fail ("
                ", !)");
}
END_TEST

START_TEST(S21_MEMCMP) {
  int res_21 = 0, res_norm = 0;
  res_21 = s21_memcmp("", "", 5) > 0 ? 1 : s21_memcmp("", "", 5) < 0 ? -1 : 0;
  res_norm = memcmp("", "", 5) > 0 ? 1 : memcmp("", "", 5) < 0 ? -1 : 0;
  ck_assert_msg(res_21 == res_norm,
                "Fail ("
                ", "
                ", 5)");
  res_21 = s21_memcmp("11", "1", 5) > 0 ? 1 : 0;
  res_norm = memcmp("11", "1", 5) > 0 ? 1 : memcmp("11", "1", 5) < 0 ? -1 : 0;
  ck_assert_int_ge(res_21, res_norm);
  res_21 = s21_memcmp("1", "11", 1) > 0 ? 1 : 0;
  res_norm = memcmp("1", "11", 1) > 0 ? 1 : memcmp("1", "11", 1) < 0 ? -1 : 0;
  ck_assert_int_eq(res_21, res_norm);
  res_21 = s21_memcmp("12", "11", 2) > 0 ? 1 : 0;
  res_norm = memcmp("12", "11", 2) > 0 ? 1 : memcmp("12", "11", 2) < 0 ? -1 : 0;
  ck_assert_int_eq(res_21, res_norm);
  res_21 = s21_memcmp("1abcde", "1abcdf", 5) > 0   ? 1
           : s21_memcmp("1abcde", "1abcdf", 5) < 0 ? -1
                                                   : 0;
  res_norm = memcmp("1abcde", "1abcdf", 5) > 0   ? 1
             : memcmp("1abcde", "1abcdf", 5) < 0 ? -1
                                                 : 0;
  ck_assert_int_eq(res_21, res_norm);
  char c[10] = "abcde";
  char nc[10] = "ab";
  res_21 = s21_memcmp(c, nc, 5) > 0 ? 1 : s21_memcmp(c, nc, 5) < 0 ? -1 : 0;
  res_norm = memcmp(c, nc, 5) > 0 ? 1 : memcmp(c, nc, 5) < 0 ? -1 : 0;
  ck_assert_int_ge(res_21, res_norm);
  res_21 = s21_memcmp(nc, c, 10) > 0 ? 1 : s21_memcmp(nc, c, 10) < 0 ? -1 : 0;
  res_norm = memcmp(nc, c, 10) > 0 ? 1 : memcmp(nc, c, 10) < 0 ? -1 : 0;
  ck_assert_msg(res_21 == res_norm, "Fail");
}
END_TEST

START_TEST(S21_MEMCPY) {
  char res_21[] = "Hello world!";
  char res_norm[] = "Hello world!";
  const char* src = "qwertyuiop[]asdfghjkl;'zxcvbnm,./1234567890-=";
  s21_memcpy(res_21, src, 1);
  memcpy(res_norm, src, 1);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
  s21_memcpy(res_21, src, 10);
  memcpy(res_norm, src, 10);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
  s21_memcpy(res_21, " ", 10);
  memcpy(res_norm, " ", 10);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
  s21_memcpy(res_21, " ", 13);
  memcpy(res_norm, " ", 13);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
  s21_memcpy(res_21, " ", 0);
  memcpy(res_norm, " ", 0);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
  s21_memcpy(res_21, "", 10);
  memcpy(res_norm, "", 10);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
  s21_memcpy(res_21, "!/.", 10);
  memcpy(res_norm, "!/.", 10);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
}
END_TEST

START_TEST(S21_MEMSET) {
  char res_21[] = "Hello world!";
  char res_norm[] = "Hello world!";
  s21_memset(res_21, '!', 3);
  memset(res_norm, '!', 3);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
  s21_memset(res_21, '&', strlen(res_21));
  memset(res_norm, '&', strlen(res_norm));
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
  s21_memset(res_21, '.', 1);
  memset(res_norm, '.', 1);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
  s21_memset(res_21, ' ', 5);
  memset(res_norm, ' ', 5);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
  s21_memset(res_21, ' ', strlen(res_21));
  memset(res_norm, ' ', strlen(res_norm));
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
}
END_TEST

START_TEST(S21_STRNCAT) {
  char res_21[999] = "Hello world!";
  char res_norm[999] = "Hello world!";
  const char* src = "?>.</'\[]";
  const char* src2 = "?>.</'\[]";
  s21_strncat(res_21, src, 9);
  strncat(res_norm, src2, 9);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
  s21_strncat(res_21, src, 1);
  strncat(res_norm, src, 1);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
  s21_strncat(res_21, " ", 2);
  strncat(res_norm, " ", 2);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
  s21_strncat(res_21, "999", 10);
  strncat(res_norm, "999", 10);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
  s21_strncat(res_21, "999777666", 10);
  strncat(res_norm, "999777666", 10);
  ck_assert_msg(strcmp(res_21, res_norm) == 0, "Fail");
}
END_TEST

START_TEST(S21_STRCHR) {
  ck_assert_msg(s21_strchr("Hello world!", 'w') == strchr("Hello world!", 'w'),
                "FAIL (Hello world!, w)");
  ck_assert_msg(s21_strchr("Hello world!", '0') == strchr("Hello world!", '0'),
                "FAIL (Hello world!, 0)");
  ck_assert_msg(s21_strchr("Hello world!", 'H') == strchr("Hello world!", 'H'),
                "FAIL (Hello world!, H)");
  ck_assert_msg(s21_strchr("Hello world!", '!') == strchr("Hello world!", '!'),
                "FAIL (Hello world!, !)");
  ck_assert_msg(s21_strchr("", 'w') == strchr("", 'w'), "FAIL ( , w)");
  ck_assert_msg(
      s21_strchr("Hello world!", '\0') == strchr("Hello world!", '\0'),
      "FAIL ( , \\0)");
}
END_TEST

START_TEST(S21_STRCSPN) {
  ck_assert_msg(s21_strcspn("Hello", "asdk") == strcspn("Hello", "asdk"),
                "FAIL (Hello, asdk)");
  ck_assert_msg(s21_strcspn("asdk", "Hello") == strcspn("asdk", "Hello"),
                "FAIL (asdk, Hello)");
  ck_assert_msg(s21_strcspn("Hello", "Hello") == strcspn("Hello", "Hello"),
                "FAIL (Hello, Hello)");
  ck_assert_msg(s21_strcspn("Hel", "Hello") == strcspn("Hel", "Hello"),
                "FAIL (Hel, Hello)");
  ck_assert_msg(s21_strcspn("Hello", "Hel") == strcspn("Hello", "Hel"),
                "FAIL (Hello, Hel)");
  ck_assert_msg(s21_strcspn("Hello", "") == strcspn("Hello", ""),
                "FAIL (Hello, )");
  ck_assert_msg(s21_strcspn("", "Hel") == strcspn("", "Hel"), "FAIL (, Hel)");
}
END_TEST

START_TEST(S21_STRERROR) {
  for (int i = -5; i < 200; i++) {
    ck_assert_int_eq(strcmp(s21_strerror(i), strerror(i)), 0);
  }
}
END_TEST

START_TEST(S21_STRNCMP) {
  int res_norm = 0;
  res_norm = strncmp("", "", 5) > 0 ? 1 : strncmp("", "", 5) < 0 ? -1 : 0;
  ck_assert_msg(s21_strncmp("", "", 1) == res_norm, "FAIL");
  res_norm = strncmp("11", "1", 5) > 0 ? 1 : strncmp("11", "1", 5) < 0 ? -1 : 0;
  ck_assert_int_ge(s21_strncmp("11", "1", 2), res_norm);
  res_norm = strncmp("1", "11", 1) > 0 ? 1 : strncmp("1", "11", 1) < 0 ? -1 : 0;
  ck_assert_int_eq(s21_strncmp("1", "11", 1), res_norm);
  res_norm = strncmp("12", "11", 2) > 0   ? 1
             : strncmp("12", "11", 2) < 0 ? -1
                                          : 0;
  ck_assert_int_eq(s21_strncmp("12", "11", 2), res_norm);
  res_norm = strncmp("1abcde", "1abcdf", 5) > 0   ? 1
             : strncmp("1abcde", "1abcdf", 5) < 0 ? -1
                                                  : 0;
  ck_assert_int_eq(s21_strncmp("1abcde", "1abcdf", 5),
                   strncmp("1abcde", "1abcdf", 5));
  char c[10] = "abcde";
  char nc[10] = "ab";
  res_norm = strncmp(c, nc, 5) > 0 ? 1 : strncmp(c, nc, 5) < 0 ? -1 : 0;
  ck_assert_int_ge(s21_strncmp(c, nc, 5), res_norm);
}
END_TEST

START_TEST(S21_STRNCPY) {
  char msg_1[50] = "";
  char msg_2[50] = "";
  ck_assert_msg(strcmp(s21_strncpy(msg_1, "", 1), strncpy(msg_2, "", 1)) == 0,
                "FAIL");
  ck_assert_msg(
      strcmp(s21_strncpy(msg_1, "TEST?", 6), strncpy(msg_2, "TEST?", 6)) == 0,
      "FAIL");
  ck_assert_msg(
      strcmp(s21_strncpy(msg_1, "HAhaHA", 8), strncpy(msg_2, "HAhaHA", 8)) == 0,
      "FAIL");
  ck_assert_msg(strcmp(s21_strncpy(msg_1, "", 2), strncpy(msg_2, "", 2)) == 0,
                "FAIL");
}
END_TEST

START_TEST(S21_STRLEN) {
  int res_strlen = 0;
  int res_s21_strlen = 0;
  res_strlen = strlen("Test/1test2/test3!");
  res_s21_strlen = s21_strlen("Test/1test2/test3!");
  ck_assert_int_eq(res_s21_strlen, res_strlen);
  res_strlen = strlen("Test/");
  res_s21_strlen = s21_strlen("Test/");
  ck_assert_int_eq(res_s21_strlen, res_strlen);
  res_strlen = strlen("T");
  res_s21_strlen = s21_strlen("T");
  ck_assert_int_eq(res_s21_strlen, res_strlen);
  res_strlen = strlen("Te");
  res_s21_strlen = s21_strlen("Te");
  ck_assert_int_eq(res_s21_strlen, res_strlen);
  res_strlen = strlen("!");
  res_s21_strlen = s21_strlen("!");
  ck_assert_int_eq(res_s21_strlen, res_strlen);
  res_strlen = strlen("");
  res_s21_strlen = s21_strlen("");
  ck_assert_int_eq(res_s21_strlen, res_strlen);
}
END_TEST

START_TEST(S21_STRPBRK) {
  char* str1 = "Test/1test2/test3!";
  char* str2 = "";
  char* str3 = "";
  ck_assert_msg(s21_strpbrk(str1, "T") == strpbrk(str1, "T"), "Fail test 1");
  ck_assert_msg(s21_strpbrk(str1, "Te") == strpbrk(str1, "Te"), "Fail test 2");
  ck_assert_msg(s21_strpbrk(str1, "e") == strpbrk(str1, "e"), "Fail test 3");
  ck_assert_msg(s21_strpbrk(str1, "1") == strpbrk(str1, "1"), "Fail test 4");
  ck_assert_msg(s21_strpbrk(str1, "1/") == strpbrk(str1, "1/"), "Fail test 5");
  ck_assert_msg(s21_strpbrk(str1, "/") == strpbrk(str1, "/"), "Fail test 6");
  ck_assert_msg(s21_strpbrk(str1, "!") == strpbrk(str1, "!"), "Fail test 7");
  ck_assert_msg(s21_strpbrk(str2, "Test") == strpbrk(str2, "Test"),
                "Fail test 8");
  ck_assert_msg(s21_strpbrk(str2, "test") == strpbrk(str2, "test"),
                "Fail test 9");
  ck_assert_msg(s21_strpbrk(str1, str3) == strpbrk(str1, str3), "Fail test 10");
  ck_assert_msg(s21_strpbrk(str2, str3) == strpbrk(str2, str3), "Fail test 11");
  ck_assert_msg(s21_strpbrk(str2, str2) == strpbrk(str2, str2), "Fail test 12");
  ck_assert_msg(s21_strpbrk(str1, str1) == strpbrk(str1, str1), "Fail test 13");
}
END_TEST

START_TEST(S21_STRRCHR) {
  char* str = "Test/1test2/test3!";
  ck_assert_msg(s21_strrchr(str, 'T') == strrchr(str, 'T'), "Fail test 1");
  ck_assert_msg(s21_strrchr(str, 't') == strrchr(str, 't'), "Fail test 2");
  ck_assert_msg(s21_strrchr(str, '1') == strrchr(str, '1'), "Fail test 3");
  ck_assert_msg(s21_strrchr(str, '0') == strrchr(str, '0'), "Fail test 4");
  ck_assert_msg(s21_strrchr(str, '/') == strrchr(str, '/'), "Fail test 5");
  ck_assert_msg(s21_strrchr(str, '!') == strrchr(str, '!'), "Fail test 6");
  ck_assert_msg(s21_strrchr(str, '\0') == strrchr(str, '\0'), "Fail test 7");
  ck_assert_msg(s21_strrchr("", 't') == strrchr("", 't'), "Fail test 8");
}
END_TEST

START_TEST(S21_STRSTR) {
  char* str = "Test/1test2/test3!";
  ck_assert_msg(s21_strstr(str, "test") == strstr(str, "test"), "Fail test 1");
  ck_assert_msg(s21_strstr(str, "st") == strstr(str, "st"), "Fail test 2");
  ck_assert_msg(s21_strstr(str, "e") == strstr(str, "e"), "Fail test 3");
  ck_assert_msg(s21_strstr(str, "!") == strstr(str, "!"), "Fail test 4");
  ck_assert_msg(s21_strstr(str, "") == strstr(str, ""), "Fail test 5");
  str = "";
  ck_assert_msg(s21_strstr(str, "") == strstr(str, ""), "Fail test 6");
}
END_TEST

START_TEST(S21_STRTOK) {
  char* result_str1 = s21_NULL;
  char* result_str2 = s21_NULL;
  char* delim1 = "|/";
  char* delim2 = "/";
  char* delim3 = "";
  do {
    char str1[] = "Te|/s|/t|/|/1|/|/test|/|/|/2|/|/|/test3";
    char str2[] = "Te|/s|/t|/|/1|/|/test|/|/|/2|/|/|/test3";
    result_str1 = strtok(str1, delim1);
    result_str2 = s21_strtok(str2, delim1);
    while (result_str2 != s21_NULL) {
      ck_assert_str_eq(result_str1, result_str2);
      result_str1 = strtok(s21_NULL, delim1);
      result_str2 = s21_strtok(NULL, delim1);
    }
    ck_assert_str_eq(str1, str2);
  } while (0);
  do {
    char str1[] = "/|Test|/1|/test2|/test3|/";
    char str2[] = "/|Test|/1|/test2|/test3|/";
    result_str1 = strtok(str1, delim1);
    result_str2 = s21_strtok(str2, delim1);
    while (result_str2 != s21_NULL) {
      ck_assert_str_eq(result_str1, result_str2);
      result_str1 = strtok(s21_NULL, delim1);
      result_str2 = s21_strtok(NULL, delim1);
    }
    ck_assert_str_eq(str1, str2);
  } while (0);
  do {
    char str1[] = "|/|/T|/|/est|/1|/test2|/test|/|/3|/|/";
    char str2[] = "|/|/T|/|/est|/1|/test2|/test|/|/3|/|/";
    result_str1 = strtok(str1, delim1);
    result_str2 = s21_strtok(str2, delim1);
    while (result_str2 != s21_NULL) {
      ck_assert_str_eq(result_str1, result_str2);
      result_str1 = strtok(s21_NULL, delim1);
      result_str2 = s21_strtok(NULL, delim1);
    }
    ck_assert_str_eq(str1, str2);
  } while (0);
  do {
    char str1[] = "Te/s/t//1//test///2///test3";
    char str2[] = "Te/s/t//1//test///2///test3";
    result_str1 = strtok(str1, delim2);
    result_str2 = s21_strtok(str2, delim2);
    while (result_str2 != s21_NULL) {
      ck_assert_str_eq(result_str1, result_str2);
      result_str1 = strtok(s21_NULL, delim2);
      result_str2 = s21_strtok(NULL, delim2);
    }
    ck_assert_str_eq(str1, str2);
  } while (0);
  do {
    char str1[] = "/Te/s/t//1//test///2///test3/";
    char str2[] = "/Te/s/t//1//test///2///test3/";
    result_str1 = strtok(str1, delim2);
    result_str2 = s21_strtok(str2, delim2);
    while (result_str2 != s21_NULL) {
      ck_assert_str_eq(result_str1, result_str2);
      result_str1 = strtok(s21_NULL, delim2);
      result_str2 = s21_strtok(NULL, delim2);
    }
    ck_assert_str_eq(str1, str2);
  } while (0);
  do {
    char str1[] = "//Te/s/t//1//test///2///test3//";
    char str2[] = "//Te/s/t//1//test///2///test3//";
    result_str1 = strtok(str1, delim2);
    result_str2 = s21_strtok(str2, delim2);
    while (result_str2 != s21_NULL) {
      ck_assert_str_eq(result_str1, result_str2);
      result_str1 = strtok(s21_NULL, delim2);
      result_str2 = s21_strtok(NULL, delim2);
    }
    ck_assert_str_eq(str1, str2);
  } while (0);
  do {
    char str1[] = "Test1test2test3";
    char str2[] = "Test1test2test3";
    result_str1 = strtok(str1, delim1);
    result_str2 = s21_strtok(str2, delim1);
    while (result_str2 != s21_NULL) {
      ck_assert_str_eq(result_str1, result_str2);
      result_str1 = strtok(s21_NULL, delim1);
      result_str2 = s21_strtok(NULL, delim1);
    }
    ck_assert_str_eq(str1, str2);
  } while (0);
  do {
    char str1[] = "Test1test2test3";
    char str2[] = "Test1test2test3";
    result_str1 = strtok(str1, delim3);
    result_str2 = s21_strtok(str2, delim3);
    ck_assert_str_eq(result_str1, result_str2);
    ck_assert_str_eq(str1, str2);
  } while (0);
  do {
    char str1[] = "";
    char str2[] = "";
    result_str1 = strtok(str1, delim1);
    result_str2 = s21_strtok(str2, delim1);
    ck_assert_ptr_null(result_str1);
    ck_assert_ptr_null(result_str2);
    ck_assert_str_eq(str1, str2);
  } while (0);
  do {
    char str1[] = "";
    char str2[] = "";
    result_str1 = strtok(str1, delim3);
    result_str2 = s21_strtok(str2, delim3);
    ck_assert_ptr_null(result_str1);
    ck_assert_ptr_null(result_str2);
    ck_assert_str_eq((char*)str1, (char*)str2);
  } while (0);
  do {
    char s1[] = "Hello,-! world!";
    char s2[] = "Hello,-! world!";
    char s3[] = "!-";
    ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
    ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
  } while (0);
  do {
    char s1[] = "";
    char s2[] = "";
    char s3[] = "";
    ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
  } while (0);
  do {
    char s1[] = "Hello, world!";
    char s2[] = "Hello, world!";
    char s3[] = "\0";
    ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
  } while (0);
  do {
    char s1[] = "Hello, world!";
    char s2[] = "Hello, world!";
    char s3[] = "";
    ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
  } while (0);
  do {
    char s1[] = "Hello, world!";
    char s2[] = "Hello, world!";
    char s3[] = "Hello, world!";
    ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
  } while (0);
  do {
    char s1[] = "Hello, world!";
    char s2[] = "Hello, world!";
    char s3[] = "My name is JULIYA-MAF.";
    ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
  } while (0);

  do {
    char s1[] = "hehehehehehehB";
    char s2[] = "hehehehehehehB";
    char s3[] = "B";
    ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
  } while (0);

  do {
    char s1[] = "\nAhehehehehehehB";
    char s2[] = "\nAhehehehehehehB";
    char s3[] = "A";
    ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
  } while (0);
  do {
    char s1[] = "\0Hello, world!";
    char s2[] = "\0Hello, world!";
    char s3[] = "\0";
    ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
  } while (0);
  do {
    char s1[] = "\0Hello, world!";
    char s2[] = "\0Hello, world!";
    char s3[] = "";
    ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
  } while (0);
  do {
    char* s1 = s21_NULL;
    char* s2 = s21_NULL;
    char s3[] = "";
    ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
  } while (0);
  do {
    char s1[] = "maf maf = maf";
    char s2[] = "maf maf = maf";
    char s3[] = "maf = maf";
    ck_assert_pstr_eq(strtok(s1, s3), s21_strtok(s2, s3));
  } while (0);

  do {
    char s1[] = "Hello,       world! And other people";
    char s2[] = "Hello,       world! And other people";
    char s3[] = "Come here";
    char s4[] = "Come here";
    char s5[] = "e";
    ck_assert_pstr_eq(strtok(s1, s5), s21_strtok(s2, s5));
    for (int i = 0; i < 5; i++) {
      ck_assert_pstr_eq(strtok(s21_NULL, s5), s21_strtok(s21_NULL, s5));
    }
    ck_assert_pstr_eq(strtok(s3, s5), s21_strtok(s4, s5));
    ck_assert_pstr_eq(strtok(s21_NULL, s5), s21_strtok(s21_NULL, s5));
    ck_assert_pstr_eq(strtok(s21_NULL, s5), s21_strtok(s21_NULL, s5));
  } while (0);

  do {
    char s1[] = "Hello,      worllllllllllld! And lother people      ";
    char s2[] = "Hello,      worllllllllllld! And lother people      ";
    char s3[] = "Come here";
    char s4[] = "Come here";
    char s5[] = " l";
    ck_assert_pstr_eq(strtok(s1, s5), s21_strtok(s2, s5));
    for (int i = 0; i < 5; i++) {
      ck_assert_pstr_eq(strtok(s21_NULL, s5), s21_strtok(s21_NULL, s5));
    }
    ck_assert_pstr_eq(strtok(s3, s5), s21_strtok(s4, s5));
    ck_assert_pstr_eq(strtok(s21_NULL, s5), s21_strtok(s21_NULL, s5));
    ck_assert_pstr_eq(strtok(s21_NULL, s5), s21_strtok(s21_NULL, s5));
  } while (0);
  do {
    char s1[] = "Helllllllo,      worllllllllllld! And lother people      ";
    char s2[] = "Helllllllo,      worllllllllllld! And lother people      ";
    char s3[] = "Come here";
    char s4[] = "Come here";
    char s5[] = "l";
    char s6[] = " ";
    ck_assert_str_eq(strtok(s1, s5), s21_strtok(s2, s5));
    for (int i = 0; i < 5; i++) {
      ck_assert_pstr_eq(strtok(s21_NULL, s6), s21_strtok(s21_NULL, s6));
    }
    ck_assert_pstr_eq(strtok(s3, s6), s21_strtok(s4, s6));
    ck_assert_pstr_eq(strtok(s21_NULL, s6), s21_strtok(s21_NULL, s6));
    ck_assert_pstr_eq(strtok(s21_NULL, s6), s21_strtok(s21_NULL, s6));
  } while (0);
  do {
    char s1[] = "RIM AMD ROM!!";
    char s2[] = "RIM AMD ROM!!";
    char s3[] = "R";
    strtok(s1, s3);
    strtok(NULL, s3);
    s21_strtok(s2, s3);
    s21_strtok(NULL, s3);
    ck_assert_pstr_eq(s1, s2);
  } while (0);
  do {
    char s1[] = "ASFERIKA";
    char s2[] = "ASFERIKA";
    char s3[] = "A";
    strtok(s1, s3);
    strtok(NULL, s3);
    strtok(NULL, s3);
    s21_strtok(s2, s3);
    s21_strtok(NULL, s3);
    s21_strtok(NULL, s3);
    ck_assert_pstr_eq(s1, s2);
  } while (0);
  do {
    char s1[] = "hrom brom maf";
    char s2[] = "hrom brom maf";
    char s3[] = "hrom bro";
    char* s4 = strtok(s1, s3);
    char* s6 = strtok(s21_NULL, s3);
    char* s5 = s21_strtok(s2, s3);
    char* s7 = s21_strtok(s21_NULL, s3);
    ck_assert_pstr_eq(s1, s2);
    ck_assert_pstr_eq(s4, s5);
    ck_assert_pstr_eq(s6, s7);
  } while (0);
  do {
    char s1[] = "AAAAAAAGGGGGHHHHH";
    char s2[] = "AAAAAAAGGGGGHHHHH";
    char s3[] = "A";
    strtok(s1, s3);
    strtok(NULL, s2);
    strtok(NULL, s2);
    s21_strtok(s2, s3);
    s21_strtok(NULL, s3);
    s21_strtok(NULL, s3);
    ck_assert_pstr_eq(s1, s2);
  } while (0);
}
END_TEST

START_TEST(S21_SSCANF) {
  do {
    char format[100] = "%c";
    char str[100] = "s";
    char a, b;
    int original = sscanf(str, format, &a);
    int s21_func = s21_sscanf(str, format, &b);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(a, b);
  } while (0);
  do {
    char format[100] = "%c";
    char str[100] = "";
    char a, b;
    int original = sscanf(str, format, &a);
    int s21_func = s21_sscanf(str, format, &b);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(a, b);
  } while (0);
  do {
    char format[100] = "%c";
    char str[100] = "hi\thi";
    char a, b;
    int original = sscanf(str, format, &a);
    int s21_func = s21_sscanf(str, format, &b);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(a, b);
  } while (0);
  do {
    char format[100] = "%c %c %c";
    char str[100] = "hi\thi h";
    char o1, o2, o3, s1, s2, s3;
    int original = sscanf(str, format, &o1, &o2, &o3);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
  } while (0);
  do {
    char format[100] = "%d %d %d 45%*d %d";
    char str[100] = "1 2 3 45 6 7";
    int o1, o2, o3, o4, s1, s2, s3, s4;
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
    ck_assert_int_eq(o4, s4);
  } while (0);
  do {
    char format[100] = "%d %d %d 45%d";
    char str[100] = "";
    char o1, o2, o3, o4, s1, s2, s3, s4;
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
    ck_assert_int_eq(o4, s4);
  } while (0);
  do {
    char format[100] = "%hd %4hd %d 45%hd";
    char str[100] = "12 23 34 45 56";
    short o1, o2, o4, s1, s2, s4;
    int o3, s3;
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
    ck_assert_int_eq(o4, s4);
  } while (0);
  do {
    char format[100] = "%ld %4ld %d 45%ld";
    char str[100] = "12 -23 34 45 56";
    long int o1, o2, o4, s1, s2, s4;
    int o3, s3;
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
    ck_assert_int_eq(o4, s4);
  } while (0);
  do {
    char format[100] = "%s";
    char str[100] = "hello my darling";
    char o1[100], s1[100];
    int original = sscanf(str, format, &o1);
    int s21_func = s21_sscanf(str, format, &s1);
    ck_assert_int_eq(original, s21_func);
    ck_assert_str_eq(o1, s1);
  } while (0);
  do {
    char format[100] = "%s %s %s";
    char str[100] = "test1 test2 test3";
    char o1[100], o2[100], o3[100];
    char s1[100], s2[100], s3[100];
    int original = sscanf(str, format, &o1, &o2, &o3);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3);
    ck_assert_int_eq(original, s21_func);
    ck_assert_str_eq(o1, s1);
    ck_assert_str_eq(o2, s2);
    ck_assert_str_eq(o3, s3);
  } while (0);
  do {
    char format[100] = "%s %% %s %s";
    char str[100] = "test1 % test2 test3 test4";
    char o1[100], o2[100], o3[100];
    char s1[100], s2[100], s3[100];
    int original = sscanf(str, format, &o1, &o2, &o3);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3);
    ck_assert_int_eq(original, s21_func);
    ck_assert_str_eq(o1, s1);
    ck_assert_str_eq(o2, s2);
    ck_assert_str_eq(o3, s3);
  } while (0);
  do {
    char format[100] = "%s %s %s %s";
    char str[100] = "test test2 test3 test4";
    char o1[100], o2[100], o3[100], o4[100];
    char s1[100], s2[100], s3[100], s4[100];
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_str_eq(o1, s1);
    ck_assert_str_eq(o2, s2);
    ck_assert_str_eq(o3, s3);
    ck_assert_str_eq(o4, s4);
  } while (0);
  do {
    char format[100] = "%14f%3f\t%2f%1f";
    char str[100] = "1.123 -0.0021 12.00001 3.01010202";
    int o1, o2, o3, o4, s1, s2, s3, s4;
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
    ck_assert_int_eq(o4, s4);
  } while (0);
  do {
    char format[100] = "%14Lf%3Lf\t%2Lf%1Lf";
    char str[100] = "-1.1e3 0.0021 12.00001 +13.010102e2";
    long double o1, o2, o3, o4, s1 = 0, s2 = 0, s3 = 0, s4 = 0;
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
    ck_assert_int_eq(o4, s4);
  } while (0);
  do {
    char format[100] = "%14i%3i\t%2i%1i";
    char str[100] = "89 -87 45 56";
    int o1, o2, o3, o4, s1, s2, s3, s4;
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
    ck_assert_int_eq(o4, s4);
  } while (0);
  do {
    char format[100] = "%14hi%3hi\t%2hi%1hi";
    char str[100] = "89 -87 45 56";
    short o1, o2, o3, o4, s1, s2, s3, s4;
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_float_eq(o1, s1);
    ck_assert_float_eq(o2, s2);
    ck_assert_float_eq(o3, s3);
    ck_assert_float_eq(o4, s4);
  } while (0);
  do {
    char format[100] = "%14li%3li\t%2li%1li";
    char str[100] = "0xafbcd 0Xf +450001122 56";
    double o1, o2, o3, o4, s1, s2, s3, s4;
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_double_eq(o1, s1);
    ck_assert_double_eq(o2, s2);
    ck_assert_double_eq(o3, s3);
    ck_assert_double_eq(o4, s4);
  } while (0);
  do {
    char format[100] = "%14lu%3lu\t%2lu%1lu";
    char str[100] = "84564564569 87 455656 56";
    unsigned long int o1, o2, o3, o4, s1, s2, s3, s4;
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
    ck_assert_int_eq(o4, s4);
  } while (0);
  do {
    char format[100] = "%14hu%3hu\t%2hu%1hu";
    char str[100] = "89 87 -5 56";
    unsigned short int o1, o2, o3, o4, s1, s2, s3, s4;
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
    ck_assert_int_eq(o4, s4);
  } while (0);
  do {
    char format[100] = "%14hu%hu\t%2hu%1hu";
    char str[100] = "9 87 45 56";
    unsigned short int o1, o2, o3, o4, s1, s2, s3, s4;
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
    ck_assert_int_eq(o4, s4);
  } while (0);
  do {
    char format[100] = "%14o%o%o";
    char str[100] = "3 7 45 6";
    unsigned int o1, o2, o3, s1, s2, s3;
    int original = sscanf(str, format, &o1, &o2, &o3);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
  } while (0);
  do {
    char format[100] = "%4ho%o%2ho%1ho";
    char str[100] = "12 34 56 78";
    unsigned short int o1, o2, o3, o4, s1, s2, s3, s4;
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
    ck_assert_int_eq(o4, s4);
  } while (0);
  do {
    char format[100] = "%o";
    char str[100] = "0X";
    int o1 = 0, s1 = 0;
    int original = sscanf(str, format, &o1);
    int s21_func = s21_sscanf(str, format, &s1);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
  } while (0);

  do {
    char format[100] = "%X %x %X";
    char str[100] = "A A A";
    int o1, o2, o3, s1, s2, s3;
    int original = sscanf(str, format, &o1, &o2, &o3);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
  } while (0);

  do {
    char format[100] = "%p %p %p";
    char str[100] = "0x7ffd5c74d840 0x7ffd5c74d844 0x7ffd5c74d848";
    int *o1, *o2, *o3, *s1, *s2, *s3;
    int original = sscanf(str, format, &o1, &o2, &o3);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3);
    ck_assert_int_eq(original, s21_func);
    ck_assert_ptr_eq(o1, s1);
    ck_assert_ptr_eq(o2, s2);
    ck_assert_ptr_eq(o3, s3);
  } while (0);

  do {
    char format[100] = "%d %n %n %n";
    char str[100] = "12  123 1234 12345";
    int o1, o2, o3, o4, s1, s2, s3, s4;
    int original = sscanf(str, format, &o1, &o2, &o3, &o4);
    int s21_func = s21_sscanf(str, format, &s1, &s2, &s3, &s4);
    ck_assert_int_eq(original, s21_func);
    ck_assert_int_eq(o1, s1);
    ck_assert_int_eq(o2, s2);
    ck_assert_int_eq(o3, s3);
    ck_assert_int_eq(o4, s4);
  } while (0);
}
END_TEST

START_TEST(SSCANF_D) {  // Тесты %d
  char* str[] = {"+123456 -654321 1+23456 6-554321 -2147483647 +2147483647",
                 "1+23456 6-554321 -2147483648 +2147483648",
                 "q+123456 -654321 1+23456 6-554321 -12345678q987654321 "
                 "+1234567898w7654321",
                 "+123456 -654321 1++23456 6-554321 -12345678q987654321 "
                 "+1234567898w7654321",
                 "--123456 -654321 1++23456 6-554321 -12345678q987654321 "
                 "+1234567898w7654321",
                 "",
                 "+1-2+3-4+5-6+ -6+5-4+3-2+1-"};
  for (int i = 0; i < 7; ++i) {  // Тесты %d без флагов
    int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0, res1 = 0;
    int d11 = 0, d12 = 0, d13 = 0, d14 = 0, d15 = 0, d16 = 0, res2 = 0;
    res1 =
        sscanf(str[i], "  %d  %d %d %d  %d %d ", &d1, &d2, &d3, &d4, &d5, &d6);
    res2 = s21_sscanf(str[i], "  %d  %d %d %d  %d %d ", &d11, &d12, &d13, &d14,
                      &d15, &d16);
    ck_assert_msg(d1 == d11, "test1 %%d %d",
                  i);  // Тесты записываемого значения %d без флагов
    ck_assert_msg(d2 == d12, "test2 %%d %d", i);
    ck_assert_msg(d3 == d13, "test3 %%d %d", i);
    ck_assert_msg(d4 == d14, "test4 %%d %d", i);
    ck_assert_msg(d5 == d15, "test5 %%d %d", i);
    ck_assert_msg(d6 == d16, "test6 %%d %d", i);
    ck_assert_msg(res1 == res2, "test7 res %%d %d",
                  i);  // Тест возвращаемого значения %d без флагов
  }
  for (int i = 0; i < 7; ++i) {  // Тесты %d с флагом ширины
    int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0, res1 = 0;
    int d11 = 0, d12 = 0, d13 = 0, d14 = 0, d15 = 0, d16 = 0, res2 = 0;
    res1 = sscanf(str[i], "  %2d %*d %3d %*d %6d %*d %8d %*d %12d %*d %15d ",
                  &d1, &d2, &d3, &d4, &d5, &d6);
    res2 =
        s21_sscanf(str[i], "  %2d %*d %3d %*d %6d %*d %8d %*d %12d %*d %15d ",
                   &d11, &d12, &d13, &d14, &d15, &d16);
    ck_assert_msg(d1 == d11, "test1 width %%d %d",
                  i);  // Тесты записываемого значения %d с флагом ширины
    ck_assert_msg(d2 == d12, "test2 width %%d %d", i);
    ck_assert_msg(d3 == d13, "test3 width %%d %d", i);
    ck_assert_msg(d4 == d14, "test4 width %%d %d", i);
    ck_assert_msg(d5 == d15, "test5 width %%d %d", i);
    ck_assert_msg(d6 == d16, "test6 width %%d %d", i);
    ck_assert_msg(res1 == res2, "test7 res width %%d %d",
                  i);  // Тест возвращаемого значения %d с флагом ширины
  }
}
END_TEST

START_TEST(SSCANF_LD_HD) {
  char* str_long[] = {"+9223372036854775807 -9223372036854775807 +32767 -32767",
                      "9223372036854775807 -9223372036854775807 32767 -3w2770"};
  for (int i = 0; i < 2; ++i) {  // Тесты %d с флагом длины
    long int ld1 = 0L, ld2 = 0L, ld11 = 0L, ld12 = 0L;
    short int hd1 = 0, hd2 = 0, hd11 = 0, hd12 = 0;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str_long[i], "%ld%ld%hd%hd", &ld1, &ld2, &hd1, &hd2);
    res2 = s21_sscanf(str_long[i], "%ld%ld%hd%hd", &ld11, &ld12, &hd11, &hd12);
    ck_assert_msg(ld1 == ld11, "test1 length %%d %d",
                  i);  // Тесты записываемого значения %d с флагом длины
    ck_assert_msg(ld2 == ld12, "test2 length %%d %d", i);
    ck_assert_msg(hd1 == hd11, "test3 length %%d %d", i);
    ck_assert_msg(hd2 == hd12, "test4 length %%d %d", i);
    ck_assert_msg(res1 == res2, "test5 res length %%d %d",
                  i);  // Тест возвращаемого значения %d с флагом длины
  }
}
END_TEST

START_TEST(SSCANF_U) {
  char* str[] = {"+123456 -654321 1+23456 6-554321 -2147483647 +2147483647",
                 "1+23456 6-554321 -2147483648 +2147483648",
                 "q+123456 -654321 1+23456 6-554321 -12345678q987654321 "
                 "+1234567898w7654321",
                 "+123456 -654321 1++23456 6-554321 -12345678q987654321 "
                 "+1234567898w7654321",
                 "--123456 -654321 1++23456 6-554321 -12345678q987654321 "
                 "+1234567898w7654321",
                 "",
                 "+1-2+3-4+5-6+ -6+5-4+3-2+1-"};
  for (int i = 0; i < 7; ++i) {  // Тесты %u без флагов
    unsigned int d1 = 0U, d2 = 0U, d3 = 0U, d4 = 0U, d5 = 0U, d6 = 0U;
    unsigned int d11 = 0U, d12 = 0U, d13 = 0U, d14 = 0U, d15 = 0U, d16 = 0U;
    int res1 = 0, res2 = 0;
    res1 =
        sscanf(str[i], "  %u  %u %u %u  %u %u ", &d1, &d2, &d3, &d4, &d5, &d6);
    res2 = s21_sscanf(str[i], "  %u  %u %u %u  %u %u ", &d11, &d12, &d13, &d14,
                      &d15, &d16);
    ck_assert_msg(d1 == d11, "test1 %%u %d",
                  i);  // Тесты записываемого значения %u без флагов
    ck_assert_msg(d2 == d12, "test2 %%u %d", i);
    ck_assert_msg(d3 == d13, "test3 %%u %d", i);
    ck_assert_msg(d4 == d14, "test4 %%u %d", i);
    ck_assert_msg(d5 == d15, "test5 %%u %d", i);
    ck_assert_msg(d6 == d16, "test6 %%u %d", i);
    ck_assert_msg(res1 == res2, "test7 res %%u %d",
                  i);  // Тест возвращаемого значения %u без флагов
  }
  for (int i = 0; i < 7; ++i) {  //Тесты %u с флагом ширины
    unsigned int d1 = 0U, d2 = 0U, d3 = 0U, d4 = 0U, d5 = 0U, d6 = 0U;
    unsigned int d11 = 0U, d12 = 0U, d13 = 0U, d14 = 0U, d15 = 0U, d16 = 0U;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str[i], "  %2u %*u %3u %*u %6u %*u %8u %*u %12u %*u %15u ",
                  &d1, &d2, &d3, &d4, &d5, &d6);
    res2 =
        s21_sscanf(str[i], "  %2u %*u %3u %*u %6u %*u %8u %*u %12u %*u %15u ",
                   &d11, &d12, &d13, &d14, &d15, &d16);
    ck_assert_msg(d1 == d11, "test1 width %%u %d",
                  i);  // Тесты записываемого значения %u с флагом ширины
    ck_assert_msg(d2 == d12, "test2 width %%u %d", i);
    ck_assert_msg(d3 == d13, "test3 width %%u %d", i);
    ck_assert_msg(d4 == d14, "test4 width %%u %d", i);
    ck_assert_msg(d5 == d15, "test5 width %%u %d", i);
    ck_assert_msg(d6 == d16, "test6 width %%u %d", i);
    ck_assert_msg(res1 == res2, "test7 res width %%u %d",
                  i);  // Тест возвращаемого значения %u с флагом ширины
  }
}
END_TEST

START_TEST(SSCANF_LU_HU) {
  char* str_long[] = {
      "+18446744073709551615 -9223372036854775807 +65535 -65535",
      "18446744073709551615 +9223372036854775809 65535 6e5535"};
  unsigned long int ld1 = 0UL, ld2 = 0UL, ld11 = 0UL, ld12 = 0UL;
  unsigned short int hd1 = 0U, hd2 = 0U, hd11 = 0U, hd12 = 0U;
  long int res1 = 0, res2 = 0;
  res1 = sscanf(str_long[0], "%lu%lu%hu%hu", &ld1, &ld2, &hd1, &hd2);
  res2 = s21_sscanf(str_long[0], "%lu%lu%hu%hu", &ld11, &ld12, &hd11, &hd12);
  ck_assert_msg(
      ld1 == ld11,
      "test1 length %%u");  // Тесты записываемого значения %u с флагом длины
  ck_assert_msg(ld2 == ld12, "test2 length %%u");
  ck_assert_msg(hd1 == hd11, "test3 length %%u");
  ck_assert_msg(hd2 == hd12, "test4 length %%u");
  ck_assert_msg(
      res1 == res2,
      "test5 res length %%u");  // Тест возвращаемого значения %u с флагом длины
  res1 = sscanf(str_long[1], "%lu%lu%hu%hu", &ld1, &ld2, &hd1, &hd2);
  res2 = s21_sscanf(str_long[1], "%lu%lu%hu%hu", &ld11, &ld12, &hd11, &hd12);
  ck_assert_msg(
      ld1 == ld11,
      "test1 length %%u");  // Тесты записываемого значения %u с флагом длины
  ck_assert_msg(ld2 == ld12, "test2 length %%u");
  ck_assert_msg(hd1 == hd11, "test3 length %%u");
  ck_assert_msg(hd2 == hd12, "test4 length %%u");
  ck_assert_msg(
      res1 == res2,
      "test5 res length %%u");  // Тест возвращаемого значения %u с флагом длины
}
END_TEST

START_TEST(SSCANF_O) {  // Тесты %o
  char* str[] = {"+1234567 7654321 01+023-0456 06-0554321",
                 "01234567 -7654321 021474 3648+ +21474364",
                 "8+123456 -654321 1+23456 6-554321 -12345678987654321 "
                 "+12345678987654321",
                 "+123456 -654321 1++23456 6-554321 -12345678987654321 "
                 "+12345678987654321",
                 "--123456 -654321 1++23456 6-554321 -12345678987654321 "
                 "+12345678987654321",
                 "+0-2+0-4+5-7+ -7+5-4+3-2+1-",
                 "+0-2+777-6453+345-52+ -10+3-a+D-2+0-",
                 "-000 -2+11-2+3-2+ -10+3-a+D-2+0-",
                 "+0q-2+11-3+2-5+ -10+3-a+D-2+0-",
                 "+07-2+6-321+1-7+ -10+3-a+D-2+0-",
                 "-07-2+6-2+3-7+ -10+3-a+D-2+0-",
                 "+00-2+5-2+3-7+ -10+3-a+D-2+0-",
                 "+0| -2+56-3+324-F+ -10+3-a+D-2+0-",
                 "+0.-2+767-42+2123-F+ -10+3-a+D-2+0-",
                 "+0321-+0123c-1+3-5+ -10+3-a+D-2+0-",
                 "-0-0+12-6+7-1+ 2+3-a+D-2+0-",
                 "-0+0+4+5-3213+ 4234+2131-a+D-2+0-",
                 "-01 +0 -2 +c-5+ 321+32-42+D-2+0-",
                 "+03 -0 -2 +c-42+ 563+432-a+D-2+0-",
                 "+0 -2 +6555 +224 +3 -32 8+c-a+D-2+0-",
                 "   \n",
                 "",
                 "77 77777777 777777777 7777777777 +77777777777 -777777777777"};
  for (int i = 0; i < 23; ++i) {  // Тесты %o без флагов
    unsigned int d1 = 0U, d2 = 0U, d3 = 0U, d4 = 0U, d5 = 0U, d6 = 0U;
    unsigned int d11 = 0U, d12 = 0U, d13 = 0U, d14 = 0U, d15 = 0U, d16 = 0U;
    int res1 = 0, res2 = 0;
    res1 =
        sscanf(str[i], "  %o  %o %o %o  %o %o ", &d1, &d2, &d3, &d4, &d5, &d6);
    res2 = s21_sscanf(str[i], "  %o  %o %o %o  %o %o ", &d11, &d12, &d13, &d14,
                      &d15, &d16);
    ck_assert_msg(d1 == d11, "test1 %%o %d",
                  i);  // Тесты записываемого значения %o без флагов
    ck_assert_msg(d2 == d12, "test2 %%o %d", i);
    ck_assert_msg(d3 == d13, "test3 %%o %d", i);
    ck_assert_msg(d4 == d14, "test4 %%o %d", i);
    ck_assert_msg(d5 == d15, "test5 %%o %d", i);
    ck_assert_msg(d6 == d16, "test6 %%o %d", i);
    ck_assert_msg(res1 == res2, "test7 res %%o %d",
                  i);  // Тест возвращаемого значения %o без флагов
  }
  for (int i = 0; i < 23; ++i) {  // Тесты %o с флагом ширины
    unsigned int d1 = 0U, d2 = 0U, d3 = 0U, d4 = 0U, d5 = 0U, d6 = 0U;
    unsigned int d11 = 0U, d12 = 0U, d13 = 0U, d14 = 0U, d15 = 0U, d16 = 0U;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str[i], "  %2o %*o %3o %*o %6o %*o %8o %*o %11o %*o %12o ",
                  &d1, &d2, &d3, &d4, &d5, &d6);
    res2 =
        s21_sscanf(str[i], "  %2o %*o %3o %*o %6o %*o %8o %*o %11o %*o %12o ",
                   &d11, &d12, &d13, &d14, &d15, &d16);
    ck_assert_msg(d1 == d11, "test1 width %%o %d",
                  i);  // Тесты записываемого значения %o с флагом ширины
    ck_assert_msg(d2 == d12, "test2 width %%o %d", i);
    ck_assert_msg(d3 == d13, "test3 width %%o %d", i);
    ck_assert_msg(d4 == d14, "test4 width %%o %d", i);
    ck_assert_msg(d5 == d15, "test5 width %%o %d", i);
    ck_assert_msg(d6 == d16, "test6 width %%o %d", i);
    ck_assert_msg(res1 == res2, "test7 res width %%o %d",
                  i);  // Тест возвращаемого значения %o с флагом ширины
  }
}
END_TEST

START_TEST(SSCANF_LO_HO) {
  char* str_long[] = {
      "+01777777777777777777777 -177777777777777777777 +077777 -077777",
      "1777777777777777777777 -1777777777777777777777  77777  787777"};
  unsigned long int ld1 = 0UL, ld2 = 0UL, ld11 = 0UL, ld12 = 0UL;
  unsigned short int hd1 = 0U, hd2 = 0U, hd11 = 0U, hd12 = 0U;
  int res1 = 0, res2 = 0;
  res1 = sscanf(str_long[0], "%lo%lo%ho%ho", &ld1, &ld2, &hd1, &hd2);
  res2 = s21_sscanf(str_long[0], "%lo%lo%ho%ho", &ld11, &ld12, &hd11, &hd12);
  ck_assert_msg(
      ld1 == ld11,
      "test1 length %%o");  // Тесты записываемого значения %o с флагом длины
  ck_assert_msg(ld2 == ld12, "test2 length %%o");
  ck_assert_msg(hd1 == hd11, "test3 length %%o");
  ck_assert_msg(hd2 == hd12, "test4 length %%o");
  ck_assert_msg(
      res1 == res2,
      "test5 res length %%o");  // Тест возвращаемого значения %o с флагом длины
  res1 = sscanf(str_long[1], "%lo%lo%ho%ho", &ld1, &ld2, &hd1, &hd2);
  res2 = s21_sscanf(str_long[1], "%lo%lo%ho%ho", &ld11, &ld12, &hd11, &hd12);
  ck_assert_msg(
      ld1 == ld11,
      "test1 length %%o");  // Тесты записываемого значения %o с флагом длины
  ck_assert_msg(ld2 == ld12, "test2 length %%o");
  ck_assert_msg(hd1 == hd11, "test3 length %%o");
  ck_assert_msg(hd2 == hd12, "test4 length %%o");
  ck_assert_msg(
      res1 == res2,
      "test5 res length %%o");  // Тест возвращаемого значения %o с флагом длины
}
END_TEST

START_TEST(SSCANF_X_P) {  // Тесты %x, %X, %p
  char* str[] = {
      "+0x4+d -4d 0xff ff -0x7FFFFFFFFFFF 0x7FFFFFFFFFFF -0x7FFFFFFFFFFF "
      "0x7FFFFFFFFFFF -0x7FFFFFFFFFFF 0x7FFFFFFFFFFF",
      "0123a4567 -765b4321 021c474 3648+ +21474364",
      "G+123456 -654321 1+23456 6-554321- -12345678987654321 "
      "+12345678987654321",
      "+123456 -654321 123456 6-554321 ++12345678987654321 "
      "+12345678987654321",
      "-abcdef -fedcba 1++23456 6-554321 -12345678987654321 "
      "+12345678987654321",
      "+0x-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0x -2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0xq-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0xa-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0x|-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0x.-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0-2+0-4+5-7+ -7+5-4+3-2+1-",
      "+0-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0 -2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0q-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0a-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0a-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0|-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0| -2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0.-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0abc-+0abc-a+c-F+ -F+c-a+D-2+0-",
      "-012-+012-a+c-F+ F+c-a+D-2+0-",
      "-0ab+0ab-a+c-F+ F+c-a+D-2+0-",
      "-01 +01 -2 +c-F+ F+c-a+D-2+0-",
      "-0b +0b -2 +c-F+ F+c-a+D-2+0-",
      "+0 -2 +2D +2c +5A 3f F+c-a+D-2+0-",
      "\n  ",
      "",
      "ff FFFFFFFF FFFFFFFFF FFFFFFFFFF +FFFFFFFFFFFFFF -FFFFFFFFFFFFFF"};
  for (int i = 0; i < 29; ++i) {  // Тесты %x без флагов
    unsigned int d1 = 0U, d2 = 0U, d3 = 0U, d4 = 0U, d5 = 0U, d6 = 0U;
    unsigned int d11 = 0U, d12 = 0U, d13 = 0U, d14 = 0U, d15 = 0U, d16 = 0U;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str[i], "  %x%x%x%x%x%x ", &d1, &d2, &d3, &d4, &d5, &d6);
    res2 = s21_sscanf(str[i], "  %x%x%x%x%x%x ", &d11, &d12, &d13, &d14, &d15,
                      &d16);
    ck_assert_msg(d1 == d11, "test1 %%x %d",
                  i);  // Тесты записываемого значения %x без флагов
    ck_assert_msg(d2 == d12, "test2 %%x %d", i);
    ck_assert_msg(d3 == d13, "test3 %%x %d", i);
    ck_assert_msg(d4 == d14, "test4 %%x %d", i);
    ck_assert_msg(d5 == d15, "test5 %%x %d", i);
    ck_assert_msg(d6 == d16, "test6 %%x %d", i);
    ck_assert_msg(res1 == res2, "test7 res %%x %d",
                  i);  // Тест возвращаемого значения %x без флагов
  }
  for (int i = 0; i < 29; ++i) {  // Тесты %x с флагом ширины
    unsigned int d1 = 0U, d2 = 0U, d3 = 0U, d4 = 0U, d5 = 0U, d6 = 0U;
    unsigned int d11 = 0U, d12 = 0U, d13 = 0U, d14 = 0U, d15 = 0U, d16 = 0U;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str[i], "  %2x %*x %3x %*x %6x %*x %8x %*x %11x %*x %12x ",
                  &d1, &d2, &d3, &d4, &d5, &d6);
    res2 =
        s21_sscanf(str[i], "  %2x %*x %3x %*x %6x %*x %8x %*x %11x %*x %12x ",
                   &d11, &d12, &d13, &d14, &d15, &d16);
    ck_assert_msg(d1 == d11, "test1 width %%x %d",
                  i);  // Тесты записываемого значения %x с флагом ширины
    ck_assert_msg(d2 == d12, "test2 width %%x %d", i);
    ck_assert_msg(d3 == d13, "test3 width %%x %d", i);
    ck_assert_msg(d4 == d14, "test4 width %%x %d", i);
    ck_assert_msg(d5 == d15, "test5 width %%x %d", i);
    ck_assert_msg(d6 == d16, "test6 width %%x %d", i);
    ck_assert_msg(res1 == res2, "test7 res width %%x %d",
                  i);  // Тест возвращаемого значения %x с флагом ширины
  }
  for (int i = 0; i < 29; ++i) {  // Тесты %p без флагов
    void *d1 = s21_NULL, *d2 = s21_NULL, *d3 = s21_NULL, *d4 = s21_NULL,
         *d5 = s21_NULL, *d6 = s21_NULL;
    void *d11 = s21_NULL, *d12 = s21_NULL, *d13 = s21_NULL, *d14 = s21_NULL,
         *d15 = s21_NULL, *d16 = s21_NULL;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str[i], "  %p%p%p%p%p%p ", &d1, &d2, &d3, &d4, &d5, &d6);
    res2 = s21_sscanf(str[i], "  %p%p%p%p%p%p ", &d11, &d12, &d13, &d14, &d15,
                      &d16);
    ck_assert_msg((unsigned int*)d1 == (unsigned int*)d11, "test1 %%p %d",
                  i);  // Тесты записываемого значения %p без флагов
    ck_assert_msg((unsigned int*)d2 == (unsigned int*)d12, "test2 %%p %d", i);
    ck_assert_msg((unsigned int*)d3 == (unsigned int*)d13, "test3 %%p %d", i);
    ck_assert_msg((unsigned int*)d4 == (unsigned int*)d14, "test4 %%p %d", i);
    ck_assert_msg((unsigned int*)d5 == (unsigned int*)d15, "test5 %%p %d", i);
    ck_assert_msg((unsigned int*)d6 == (unsigned int*)d16, "test6 %%p %d", i);
    ck_assert_msg(res1 == res2, "test7 res %%p %d",
                  i);  // Тест возвращаемого значения %p без флагов
  }
  for (int i = 0; i < 29; ++i) {  // Тесты %p с флагом ширины
    void *d1 = s21_NULL, *d2 = s21_NULL, *d3 = s21_NULL, *d4 = s21_NULL,
         *d5 = s21_NULL, *d6 = s21_NULL;
    void *d11 = s21_NULL, *d12 = s21_NULL, *d13 = s21_NULL, *d14 = s21_NULL,
         *d15 = s21_NULL, *d16 = s21_NULL;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str[i], "  %2p %*p %3p %*p %6p %*p %8p %*p %11p %*p %12p ",
                  &d1, &d2, &d3, &d4, &d5, &d6);
    res2 =
        s21_sscanf(str[i], "  %2p %*p %3p %*p %6p %*p %8p %*p %11p %*p %12p ",
                   &d11, &d12, &d13, &d14, &d15, &d16);
    ck_assert_msg((unsigned int*)d1 == (unsigned int*)d11, "test1 width %%p %d",
                  i);  // Тесты записываемого значения %p с флагом ширины
    ck_assert_msg((unsigned int*)d2 == (unsigned int*)d12, "test2 width %%p %d",
                  i);
    ck_assert_msg((unsigned int*)d3 == (unsigned int*)d13, "test3 width %%p %d",
                  i);
    ck_assert_msg((unsigned int*)d4 == (unsigned int*)d14, "test4 width %%p %d",
                  i);
    ck_assert_msg((unsigned int*)d5 == (unsigned int*)d15, "test5 width %%p %d",
                  i);
    ck_assert_msg((unsigned int*)d6 == (unsigned int*)d16, "test6 width %%p %d",
                  i);
    ck_assert_msg(res1 == res2, "test7 res width %%p %d",
                  i);  // Тест возвращаемого значения %p с флагом ширины
  }
}
END_TEST

START_TEST(SSCANF_LX_HX) {
  char* str_long[] = {// Тесты %x с флагом длины
                      "+0x7ffffffffff -0x7ffffffff +0x7F -0x7fF",
                      "+07ffffffffff -07ffffffff +07Ff -07fF",
                      "7fffffffffffff -7fffffffff  7FF  7Hf"};

  unsigned long int ld1 = 0UL, ld2 = 0UL, ld11 = 0UL, ld12 = 0UL;
  unsigned short int hd1 = 0U, hd2 = 0U, hd11 = 0U, hd12 = 0U;
  int long res1 = 0, res2 = 0;
  res1 = sscanf(str_long[0], "%lx%lx%hx%hx", &ld1, &ld2, &hd1, &hd2);
  res2 = s21_sscanf(str_long[0], "%lx%lx%hx%hx", &ld11, &ld12, &hd11, &hd12);

  ck_assert_int_eq(ld1,
                   ld11);  // Тесты записываемого значения %x с флагом длины
  ck_assert_int_eq(ld2, ld12);
  ck_assert_int_eq(hd1, hd11);
  ck_assert_int_eq(hd2, hd12);  // Тест возвращаемого значения %x с флагом длины
  ck_assert_int_eq(res1, res2);
  res1 = sscanf(str_long[1], "%lx%lx%hx%hx", &ld1, &ld2, &hd1, &hd2);
  res2 = s21_sscanf(str_long[1], "%lx%lx%hx%hx", &ld11, &ld12, &hd11, &hd12);
  ck_assert_double_eq(ld1,
                      ld11);  // Тесты записываемого значения %x с флагом длины
  ck_assert_double_eq(ld2, ld12);
  ck_assert_int_eq(hd1, hd11);
  ck_assert_int_eq(hd2, hd12);  // Тест возвращаемого значения %x с флагом длины
  ck_assert_int_eq(res1, res2);
  res1 = sscanf(str_long[2], "%lx%lx%hx%hx", &ld1, &ld2, &hd1, &hd2);
  res2 = s21_sscanf(str_long[2], "%lx%lx%hx%hx", &ld11, &ld12, &hd11, &hd12);
  ck_assert_double_eq(ld1,
                      ld11);  // Тесты записываемого значения %x с флагом длины
  ck_assert_double_eq(ld2, ld12);
  ck_assert_int_eq(hd1, hd11);
  ck_assert_int_eq(hd2, hd12);  // Тест возвращаемого значения %x с флагом длины
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(SSCANF_I) {  // Тесты %i
  char* str[] = {
      "44 0x4d 0xf 0321 -07777 0x7FFFFFFFFFFF -0x7FFFFFFFFFFF ",
      "+0x4+d -4d 0xff ff -0x7FFFFFFFFFFF 0x7FFFFFFFFFFF -0x7FFFFFFFFFFF "
      "0x7FFFFFFFFFFF -0x7FFFFFFFFFFF 0x7FFFFFFFFFFF",
      "0123a4567 -765b4321 021c474 3648+ +21474364",
      "G+123456 -654321 1+23456 6-554321- -12345678987654321 "
      "+12345678987654321",
      "+123456 -654321 123456 6-554321 ++12345678987654321 "
      "+12345678987654321",
      "-abcdef -fedcba 1++23456 6-554321 -12345678987654321 "
      "+12345678987654321",
      "+0x-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0x -2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0xq-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0xa-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0x|-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0x.-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0-2+0-4+5-7+ -7+5-4+3-2+1-",
      "+0-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0 -2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0q-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0a-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0a-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0|-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0| -2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0.-2+D-a+c-F+ -F+c-a+D-2+0-",
      "+0abc-+0abc-a+c-F+ -F+c-a+D-2+0-",
      "-012-+012-a+c-F+ F+c-a+D-2+0-",
      "-0ab+0ab-a+c-F+ F+c-a+D-2+0-",
      "-01 +01 -2 +c-F+ F+c-a+D-2+0-",
      "-0b +0b -2 +c-F+ F+c-a+D-2+0-",
      "+0 -2 +2D +2c +5A 3f F+c-a+D-2+0-",
      "\n  ",
      "",
      "ff FFFFFFFF FFFFFFFFF FFFFFFFFFF +FFFFFFFFFFFFFF -FFFFFFFFFFFFFF"};
  for (int i = 0; i < 30; ++i) {  // Тесты %i без флагов
    unsigned int d1 = 0U, d2 = 0U, d3 = 0U, d4 = 0U, d5 = 0U, d6 = 0U,
                 res1 = 0U;
    unsigned int d11 = 0U, d12 = 0U, d13 = 0U, d14 = 0U, d15 = 0U, d16 = 0U,
                 res2 = 0U;
    res1 = sscanf(str[i], "  %i%i%i%i%i%i ", &d1, &d2, &d3, &d4, &d5, &d6);
    res2 = s21_sscanf(str[i], "  %i%i%i%i%i%i ", &d11, &d12, &d13, &d14, &d15,
                      &d16);
    ck_assert_msg(d1 == d11, "test1 %%i %d",
                  i);  // Тесты записываемого значения %i без флагов
    ck_assert_msg(d2 == d12, "test2 %%i %d", i);
    ck_assert_msg(d3 == d13, "test3 %%i %d", i);
    ck_assert_msg(d4 == d14, "test4 %%i %d", i);
    ck_assert_msg(d5 == d15, "test5 %%i %d", i);
    ck_assert_msg(d6 == d16, "test6 %%i %d", i);
    ck_assert_msg(res1 == res2, "test7res %%i %d",
                  i);  // Тест возвращаемого значения %i без флагов
  }
  for (int i = 0; i < 30; ++i) {  // Тесты %i с флагом ширины
    unsigned int d1 = 0U, d2 = 0U, d3 = 0U, d4 = 0U, d5 = 0U, d6 = 0U,
                 res1 = 0U;
    unsigned int d11 = 0U, d12 = 0U, d13 = 0U, d14 = 0U, d15 = 0U, d16 = 0U,
                 res2 = 0U;
    res1 = sscanf(str[i], "  %2i %*i %3i %*i %6i %*i %8i %*i %11i %*i %12i ",
                  &d1, &d2, &d3, &d4, &d5, &d6);
    res2 =
        s21_sscanf(str[i], "  %2i %*i %3i %*i %6i %*i %8i %*i %11i %*i %12i ",
                   &d11, &d12, &d13, &d14, &d15, &d16);
    ck_assert_msg(d1 == d11, "test1 width %%i %d",
                  i);  // Тесты записываемого значения %i с флагом ширины
    ck_assert_msg(d2 == d12, "test2 width %%i %d", i);
    ck_assert_msg(d3 == d13, "test3 width %%i %d", i);
    ck_assert_msg(d4 == d14, "test4 width %%i %d", i);
    ck_assert_msg(d5 == d15, "test5 width %%i %d", i);
    ck_assert_msg(d6 == d16, "test6 width %%i %d", i);
    ck_assert_msg(res1 == res2, "test7 res width %%i %d",
                  i);  // Тест возвращаемого значения %i с флагом ширины
  }
}
END_TEST

START_TEST(SSCANF_LI_HI) {
  char* str_long[] = {
      // Тесты %i с флагом длины
      "+0x7fffffffffffffff -0x7fffffffffffffff +0x7FFF -0x7FFF",
      "+0177777777777777777777 -1777777777777777777 +077777 -077777",
      "+0177777777777q77777 -1777777777777777777 +077777 -077777",
      "+9223372036854775807 -9223372036854775807 +32767 -32767"};
  unsigned long int ld1 = 0UL, ld2 = 0UL, ld11 = 0UL, ld12 = 0UL;
  unsigned short int hd1 = 0U, hd2 = 0U, hd11 = 0U, hd12 = 0U;
  int res1 = 0, res2 = 0;
  res1 = sscanf(str_long[0], "%li%li%hi%hi", &ld1, &ld2, &hd1, &hd2);
  res2 = s21_sscanf(str_long[0], "%li%li%hi%hi", &ld11, &ld12, &hd11, &hd12);
  ck_assert_msg(
      ld1 == ld11,
      "test2 length %%i");  // Тесты записываемого значения %i с флагом длины
  ck_assert_msg(ld2 == ld12, "test2 length %%i");
  ck_assert_msg(hd1 == hd11, "test4 length %%i");
  ck_assert_msg(hd2 == hd12, "test4 length %%i");
  ck_assert_msg(
      res1 == res2,
      "test5 res length %%i");  // Тест возвращаемого значения %i с флагом длины
  res1 = sscanf(str_long[1], "%li%li%hi%hi", &ld1, &ld2, &hd1, &hd2);
  res2 = s21_sscanf(str_long[1], "%li%li%hi%hi", &ld11, &ld12, &hd11, &hd12);
  ck_assert_msg(
      ld1 == ld11,
      "test2 length %%i");  // Тесты записываемого значения %i с флагом длины
  ck_assert_msg(ld2 == ld12, "test2 length %%i");
  ck_assert_msg(hd1 == hd11, "test4 length %%i");
  ck_assert_msg(hd2 == hd12, "test4 length %%i");
  ck_assert_msg(
      res1 == res2,
      "test5 res length %%i");  // Тест возвращаемого значения %i с флагом длины
  res1 = sscanf(str_long[2], "%li%li%hi%hi", &ld1, &ld2, &hd1, &hd2);
  res2 = s21_sscanf(str_long[2], "%li%li%hi%hi", &ld11, &ld12, &hd11, &hd12);
  ck_assert_msg(
      ld1 == ld11,
      "test2 length %%i");  // Тесты записываемого значения %i с флагом длины
  ck_assert_msg(ld2 == ld12, "test2 length %%i");
  ck_assert_msg(hd1 == hd11, "test4 length %%i");
  ck_assert_msg(hd2 == hd12, "test4 length %%i");
  ck_assert_msg(
      res1 == res2,
      "test5 res length %%i");  // Тест возвращаемого значения %i с флагом длины
  res1 = sscanf(str_long[3], "%li%li%hi%hi", &ld1, &ld2, &hd1, &hd2);
  res2 = s21_sscanf(str_long[3], "%li%li%hi%hi", &ld11, &ld12, &hd11, &hd12);
  ck_assert_msg(
      ld1 == ld11,
      "test2 length %%i");  // Тесты записываемого значения %i с флагом длины
  ck_assert_msg(ld2 == ld12, "test2 length %%i");
  ck_assert_msg(hd1 == hd11, "test4 length %%i");
  ck_assert_msg(hd2 == hd12, "test4 length %%i");
  ck_assert_msg(
      res1 == res2,
      "test5 res length %%i");  // Тест возвращаемого значения %i с флагом длины
}
END_TEST

START_TEST(SSCANF_F) {  // Тесты %f %g %G %e %E
  char* str[] = {"12.345 67.890 3.14159 987.62e-1 0.123 45.678",
                 "-0.123 4.5678 -9.8765 1.23456 7.89012 -2.34567",
                 ".0.e01 123 10000.0 12345.67 -9876.54321 0.00001 555.555",
                 "3.14159 2.71828 1.61803 0.57721 0.30103 -1.41421",
                 "123.456 789.012 345.678 901.234 567.890 234.567",
                 "-1.23456 -7.89012 2.34567 -0.12345 4.56789 -9.87654",
                 "1 +1.1 -.21 +0.000001 -3.4E+21 3.4E+21",
                 "1.1e2 .+21  3.e4E+21 2.5E+21",
                 "+.21 .e+21 3.e4E+21 2.5E+21",
                 ".+e21 .87654e21 3.e4E+21 2.5E+21",
                 "e+.21 .87654e21 3.e4E+21 2.5E+21",
                 "e. .87654e21 3.e4E+21 2.5E+21",
                 "e+. .87654e21 3.e4E+21 2.5E+21",
                 "+e. .87654e21 3.e4E+21 2.5E+21",
                 ".+21 .87654e21 3.e4E+21 2.5E+21",
                 ".e+21 .87654e21 3.e4E+21 2.5E+21",
                 "+.e21 .87654e21 3.e4E+21 2.5E+21",
                 "+. .87654e21 3.e4E+21 2.5E+21",
                 "1+.+e21 .87654e21 3.e4E+21 2.5E+21",
                 "1+e.+21 .87654e21 3.e4E+21 2.5E+21",
                 "1.+e21 .87654e21 3.e4E+21 2.5E+21",
                 "1+e.21 .87654e21 3.e4E+21 2.5E+21",
                 "1+.+21 .87654e21 3.e4E+21 2.5E+21",
                 "1e+.+21 .87654e21 3.e4E+21 2.5E+21",
                 "1e.e21 .87654e21 3.e4E+21 2.5E+21",
                 "1+.e+21 .87654e21 3.e4E+21 2.5E+21",
                 "1e.21 +.21 3.e4E+21 2.5E+21",
                 "1+.21 .+e21 3.e4E+21 2.5E+21",
                 "1e+.21 e+.21 3.e4E+21 2.5E+21",
                 "1.+21 e. 3.e4E+21 2.5E+21",
                 "1.21 e+. 3.e4E+21 2.5E+21",
                 "1.e21 +e. 3.e4E+21 2.5E+21",
                 "",
                 "1.e+21 .+21  3.e4E+21 2.5E+21"};
  for (int i = 0; i < 34; ++i) {  // Тесты %f без флагов
    float d1 = 0.0, d2 = 0.0, d3 = 0.0, d4 = 0.0, d5 = 0.0, d6 = 0.0;
    float d11 = 0.0, d12 = 0.0, d13 = 0.0, d14 = 0.0, d15 = 0.0, d16 = 0.0;
    int res2 = 0, res1 = 0;
    res1 = sscanf(str[i], " %f%f%f%f%f%f ", &d1, &d2, &d3, &d4, &d5, &d6);
    res2 = s21_sscanf(str[i], " %f%f%f%f%f%f ", &d11, &d12, &d13, &d14, &d15,
                      &d16);
    ck_assert_msg(d1 == d11, "test1 %%f %d",
                  i);  // Тесты записываемого значения %f без флагов
    ck_assert_msg(d2 == d12, "test2 %%f %d", i);
    ck_assert_msg(d3 == d13, "test3 %%f %d", i);
    ck_assert_msg(d4 == d14, "test4 %%f %d", i);
    ck_assert_msg(d5 == d15, "test5 %%f %d", i);
    ck_assert_msg(d6 == d16, "test6 %%f %d", i);
    ck_assert_msg(res1 == res2, "test7 res %%f %d",
                  i);  // Тест возвращаемого значения %f без флагов
  }
  for (int i = 0; i < 34; ++i) {  // Тесты %f с флагом ширины
    float d1 = 0.0, d2 = 0.0, d3 = 0.0, d4 = 0.0, d5 = 0.0, d6 = 0.0;
    float d11 = 0.0, d12 = 0.0, d13 = 0.0, d14 = 0.0, d15 = 0.0, d16 = 0.0;
    int res2 = 0, res1 = 0;
    res1 = sscanf(str[i], " %2f%*f%4f%*f%6f%*f%8f%*f%10f%*f%12f%*f ", &d1, &d2,
                  &d3, &d4, &d5, &d6);
    res2 = s21_sscanf(str[i], " %2f%*f%4f%*f%6f%*f%8f%*f%10f%*f%12f%*f ", &d11,
                      &d12, &d13, &d14, &d15, &d16);
    ck_assert_msg(d1 == d11, "test1 width %%f %d",
                  i);  // Тесты записываемого значения %f с флагом ширины
    ck_assert_msg(d2 == d12, "test2 width %%f %d", i);
    ck_assert_msg(d3 == d13, "test3 width %%f %d", i);
    ck_assert_msg(d4 == d14, "test4 width %%f %d", i);
    ck_assert_msg(d5 == d15, "test5 width %%f %d", i);
    ck_assert_msg(d6 == d16, "test6 width %%f %d", i);
    ck_assert_msg(res1 == res2, "test7 res width %%f %d",
                  i);  // Тест возвращаемого значения %f с флагом ширины
  }
  for (int i = 0; i < 34; ++i) {  // Тесты %e без флагов
    float d1 = 0.0, d2 = 0.0, d3 = 0.0, d4 = 0.0, d5 = 0.0, d6 = 0.0;
    float d11 = 0.0, d12 = 0.0, d13 = 0.0, d14 = 0.0, d15 = 0.0, d16 = 0.0;
    int res2 = 0, res1 = 0;
    res1 = sscanf(str[i], " %e%e%e%e%e%e ", &d1, &d2, &d3, &d4, &d5, &d6);
    res2 = s21_sscanf(str[i], " %e%e%e%e%e%e ", &d11, &d12, &d13, &d14, &d15,
                      &d16);
    ck_assert_msg(d1 == d11, "test1 %%e %d",
                  i);  // Тесты записываемого значения %e без флагов
    ck_assert_msg(d2 == d12, "test2 %%e %d", i);
    ck_assert_msg(d3 == d13, "test3 %%e %d", i);
    ck_assert_msg(d4 == d14, "test4 %%e %d", i);
    ck_assert_msg(d5 == d15, "test5 %%e %d", i);
    ck_assert_msg(d6 == d16, "test6 %%e %d", i);
    ck_assert_msg(res1 == res2, "test7 res %%e %d",
                  i);  // Тест возвращаемого значения %e без флагов
  }
  for (int i = 0; i < 34; ++i) {  // Тесты %e с флагом ширины
    float d1 = 0.0, d2 = 0.0, d3 = 0.0, d4 = 0.0, d5 = 0.0, d6 = 0.0;
    float d11 = 0.0, d12 = 0.0, d13 = 0.0, d14 = 0.0, d15 = 0.0, d16 = 0.0;
    int res2 = 0, res1 = 0;
    res1 = sscanf(str[i], " %2e%*e%4e%*e%6e%*e%8e%*e%10e%*e%12e%*e ", &d1, &d2,
                  &d3, &d4, &d5, &d6);
    res2 = s21_sscanf(str[i], " %2e%*e%4e%*e%6e%*e%8e%*e%10e%*e%12e%*e ", &d11,
                      &d12, &d13, &d14, &d15, &d16);
    ck_assert_msg(d1 == d11, "test1 width %%e %d",
                  i);  // Тесты записываемого значения %e с флагом ширины
    ck_assert_msg(d2 == d12, "test2 width %%e %d", i);
    ck_assert_msg(d3 == d13, "test3 width %%e %d", i);
    ck_assert_msg(d4 == d14, "test4 width %%e %d", i);
    ck_assert_msg(d5 == d15, "test5 width %%e %d", i);
    ck_assert_msg(d6 == d16, "test6 width %%e %d", i);
    ck_assert_msg(res1 == res2, "test7 res width %%e %d",
                  i);  // Тест возвращаемого значения %e с флагом ширины
  }
  for (int i = 0; i < 34; ++i) {  // Тесты %g без флагов
    float d1 = 0.0, d2 = 0.0, d3 = 0.0, d4 = 0.0, d5 = 0.0, d6 = 0.0;
    float d11 = 0.0, d12 = 0.0, d13 = 0.0, d14 = 0.0, d15 = 0.0, d16 = 0.0;
    int res2 = 0, res1 = 0;
    res1 = sscanf(str[i], " %g%g%g%g%g%g ", &d1, &d2, &d3, &d4, &d5, &d6);
    res2 = s21_sscanf(str[i], " %g%g%g%g%g%g ", &d11, &d12, &d13, &d14, &d15,
                      &d16);
    ck_assert_msg(d1 == d11, "test1 %%g %d",
                  i);  // Тесты записываемого значения %g без флагов
    ck_assert_msg(d2 == d12, "test2 %%g %d", i);
    ck_assert_msg(d3 == d13, "test3 %%g %d", i);
    ck_assert_msg(d4 == d14, "test4 %%g %d", i);
    ck_assert_msg(d5 == d15, "test5 %%g %d", i);
    ck_assert_msg(d6 == d16, "test6 %%g %d", i);
    ck_assert_msg(res1 == res2, "test7 res %%g %d",
                  i);  // Тест возвращаемого значения %g без флагов
  }
  for (int i = 0; i < 34; ++i) {  // Тесты %g с флагом ширины
    float d1 = 0.0, d2 = 0.0, d3 = 0.0, d4 = 0.0, d5 = 0.0, d6 = 0.0;
    float d11 = 0.0, d12 = 0.0, d13 = 0.0, d14 = 0.0, d15 = 0.0, d16 = 0.0;
    int res2 = 0, res1 = 0;
    res1 = sscanf(str[i], " %2g%*g%4g%*g%6g%*g%8g%*g%10g%*g%12g%*g ", &d1, &d2,
                  &d3, &d4, &d5, &d6);
    res2 = s21_sscanf(str[i], " %2g%*g%4g%*g%6g%*g%8g%*g%10g%*g%12g%*g ", &d11,
                      &d12, &d13, &d14, &d15, &d16);
    ck_assert_msg(d1 == d11, "test1 width %%g %d",
                  i);  // Тесты записываемого значения %g с флагом ширины
    ck_assert_msg(d2 == d12, "test2 width %%g %d", i);
    ck_assert_msg(d3 == d13, "test3 width %%g %d", i);
    ck_assert_msg(d4 == d14, "test4 width %%g %d", i);
    ck_assert_msg(d5 == d15, "test5 width %%g %d", i);
    ck_assert_msg(d6 == d16, "test6 width %%g %d", i);
    ck_assert_msg(res1 == res2, "test7 res width %%g %d",
                  i);  // Тест возвращаемого значения %g с флагом ширины
  }
}
END_TEST

START_TEST(SSCANF_LF) {
  char* str_long =
      "1797693134862315708145274237317043567980705675258449965989174768031572"
      "6078002853876058955863276687817154045895351438246423432132688946418276"
      "846754670353751698604991057655128207624549009038932894407586850e-5 "
      "-179769313486231570814527423731704356798070567525844996598917476803157"
      "2607800285387605895586327668781715404589535143824642343213268894641827"
      "6846754670353751698604991057655128207624549009038932894407586850845513"
      "3942304583236903222948165808559332123348274797826204144723168738177180"
      "91929e+5";
  do {  // Тест  %f с флагом длины
    long double ld1 = 0.0, ld2 = 0.0, ld11 = 0.0, ld12 = 0.0;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str_long, " %Lf %Lf ", &ld1, &ld2);
    res2 = s21_sscanf(str_long, " %Lf %Lf ", &ld11, &ld12);
    char str1[1000] = {0}, str2[1000] = {0}, str11[1000] = {0},
         str12[1000] = {0};
    snprintf(str1, sizeof(str1), "%Lf",
             ld1);  // Превращаем значение переменной в строку и записываем в
                    // массив
    snprintf(str2, sizeof(str2), "%Lf", ld2);
    snprintf(str11, sizeof(str11), "%Lf", ld11);
    snprintf(str12, sizeof(str12), "%Lf", ld12);
    ck_assert_msg(
        strlen(str1) == s21_strlen(str11),
        "test1 length %%Lf");  // Сравниваем количество символов в массиве
    ck_assert_msg(strlen(str2) == s21_strlen(str12), "test2 length %%Lf");
    ck_assert_msg(res1 == res2, "test3 res length %%Lf");
  } while (0);
  do {  // Тест  %e с флагом длины
    long double ld1 = 0.0, ld2 = 0.0, ld11 = 0.0, ld12 = 0.0;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str_long, " %Le %Le ", &ld1, &ld2);
    res2 = s21_sscanf(str_long, " %Le %Le ", &ld11, &ld12);
    char str1[1000] = {0}, str2[1000] = {0}, str11[1000] = {0},
         str12[1000] = {0};
    snprintf(str1, sizeof(str1), "%Le",
             ld1);  // Превращаем значение переменной  в строку и записываем в
                    // массив
    snprintf(str2, sizeof(str2), "%Le", ld2);
    snprintf(str11, sizeof(str11), "%Le", ld11);
    snprintf(str12, sizeof(str12), "%Le", ld12);
    ck_assert_msg(
        strlen(str1) == s21_strlen(str11),
        "test1 length %%Le");  // Сравниваем количество символов в массив
    ck_assert_msg(strlen(str2) == s21_strlen(str12), "test2 length %%Le");
    ck_assert_msg(res1 == res2, "test3 res length %%Le");
  } while (0);
  do {  // Тест  %g с флагом длины
    long double ld1 = 0.0, ld2 = 0.0, ld11 = 0.0, ld12 = 0.0;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str_long, " %Lg %Lg ", &ld1, &ld2);
    res2 = s21_sscanf(str_long, " %Lg %Lg ", &ld11, &ld12);
    char str1[1000] = {0}, str2[1000] = {0}, str11[1000] = {0},
         str12[1000] = {0};
    snprintf(str1, sizeof(str1), "%Lg",
             ld1);  // Превращаем значение переменной  в строку и записываем в
                    // массив
    snprintf(str2, sizeof(str2), "%Lg", ld2);
    snprintf(str11, sizeof(str11), "%Lg", ld11);
    snprintf(str12, sizeof(str12), "%Lg", ld12);
    ck_assert_msg(
        strlen(str1) == s21_strlen(str11),
        "test1 length %%Lg");  // Сравниваем количество символов в массив
    ck_assert_msg(strlen(str2) == s21_strlen(str12), "test2 length %%Lg");
    ck_assert_msg(res1 == res2, "test3 res length %%Lg");
  } while (0);
  do {  // Тест покрытия условия %f с флагом длины и невалидными символами
    char* str_long1 = "1e+.21 1+.+e21 3.e4E+21 2.5E+21";
    long double ld1 = 0.0, ld2 = 0.0, ld11 = 0.0, ld12 = 0.0, ld3 = 0, ld13 = 0;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str_long1, " %Lf %Lf %Lf", &ld1, &ld2, &ld3);
    res2 = s21_sscanf(str_long1, " %Lf %Lf %Lf", &ld11, &ld12, &ld13);
    char str1[1000] = {0}, str2[1000] = {0}, str11[1000] = {0},
         str12[1000] = {0}, str3[1000] = {0}, str13[1000] = {0};
    snprintf(str1, sizeof(str1), "%Lf",
             ld1);  // Превращаем значение переменной в строку и записываем в
                    // массив
    snprintf(str2, sizeof(str2), "%Lf", ld2);
    snprintf(str3, sizeof(str3), "%Lf", ld3);
    snprintf(str11, sizeof(str11), "%Lf", ld11);
    snprintf(str12, sizeof(str12), "%Lf", ld12);
    snprintf(str13, sizeof(str13), "%Lf", ld13);
    ck_assert_msg(
        strlen(str1) == s21_strlen(str11),
        "test1 length %%Lf");  // Сравниваем количество символов в массиве
    ck_assert_msg(strlen(str2) == s21_strlen(str12), "test2 length %%Lf");
    ck_assert_msg(strlen(str3) == s21_strlen(str13), "test3 length %%Lf");
    ck_assert_msg(res1 == res2, "test4 res length %%Lf");
  } while (0);
  do {  // Тест покрытия условия %f с флагом длины и невалидными символами
    char* str_long1 = ".0.e1 123 1+.+e21 3.e4E+21 2.5E+21";
    long double ld1 = 0.0, ld2 = 0.0, ld11 = 0.0, ld12 = 0.0, ld3 = 0, ld13 = 0;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str_long1, " %Lf %Lf %Lf", &ld1, &ld2, &ld3);
    res2 = s21_sscanf(str_long1, " %Lf %Lf %Lf", &ld11, &ld12, &ld13);
    char str1[1000] = {0}, str2[1000] = {0}, str11[1000] = {0},
         str12[1000] = {0}, str3[1000] = {0}, str13[1000] = {0};
    snprintf(str1, sizeof(str1), "%Lf",
             ld1);  // Превращаем значение переменной в строку и записываем в
                    // массив
    snprintf(str2, sizeof(str2), "%Lf", ld2);
    snprintf(str3, sizeof(str3), "%Lf", ld3);
    snprintf(str11, sizeof(str11), "%Lf", ld11);
    snprintf(str12, sizeof(str12), "%Lf", ld12);
    snprintf(str13, sizeof(str13), "%Lf", ld13);
    ck_assert_msg(
        strlen(str1) == s21_strlen(str11),
        "test1 length %%Lf");  // Сравниваем количество символов в массиве
    ck_assert_msg(strlen(str2) == s21_strlen(str12), "test2 length %%Lf");
    ck_assert_msg(strlen(str3) == s21_strlen(str13), "test3 length %%Lf");
    ck_assert_msg(res1 == res2, "test4 res length %%Lf");
  } while (0);
}
END_TEST

START_TEST(SSCANF_C_S) {  // Тесты %s, %c, %%, str=str
  char* str[] = {
      " %aewqbce3sXUXp:o( |pd<m8o#D4CF!7k3-0nhII ^u2nm-BN_}yU2+;O "
      "aW[Z:~I1KEVV=<J +U;!:Kse~nRA=12 {=IM?Z$L$0E+s&Ta fdsfewf",
      "Q:zWfQm oNgSXp Tmn%%|(ZaQ%%H=hY8oO6B1E()qo@>N&;} "
      "h!]H(xIR|yAH^_rGn{X ]h:;G@M0_H@@Io,$ 2erf2f aU91PCw=AAg+{H 3425 ",
      "Nat8k@j 5i^!2`8.btO  xXOoXcaFHwofV}GYjT7%%XE(<+Z<\?f "
      "H:<^ML!vwGOy#t#pff?Cz1{Q <cN@/< b[Xmd}(M fsdwe",
      "  $ C?uW   \1|ln'c;^mv{/s^#Ff}Wz     "
      "Qcb.)9RhSJlt;jx,!7KNF7O~xo\n.Z,Yv#,|@2Z[DI{FZRSu' }|m gBY?/}4WL|w "
      "12343qweqweqweqweqweqweqwe",
      "",
      "q ",
      " :   :]La.#{I9bF `{*6Z%%a<>O-\vxCuAI)(iLA InL53Tj5 p2 c "
      "R)De<tjB4=}jCtiBbU5x_(C^5\n?4~( fdswe"};
  for (int i = 0; i < 7; ++i) {  //  Тесты %s без флагов
    char d1[100] = {0}, d2[100] = {0}, d3[100] = {0}, d4[100] = {0},
         d5[100] = {0}, d6[100] = {0};
    char d11[100] = {0}, d12[100] = {0}, d13[100] = {0}, d14[100] = {0},
         d15[100] = {0}, d16[100] = {0};
    int res1 = 0, res2 = 0;
    res1 = sscanf(str[i], "  %s%s%s%s%s   %s ", d1, d2, d3, d4, d5, d6);
    res2 =
        s21_sscanf(str[i], "  %s%s%s%s%s   %s ", d11, d12, d13, d14, d15, d16);
    ck_assert_str_eq(d1,
                     d11);  // Тесты записываемого значения %s без флагов
    ck_assert_str_eq(d2, d12);
    ck_assert_str_eq(d3, d13);
    ck_assert_str_eq(d4, d14);
    ck_assert_str_eq(d5, d15);
    ck_assert_str_eq(d6, d16);
    ck_assert_msg(res1 == res2, "test res %%s %d",
                  i);  // Тест возвращаемого значения %s без флагов
  }
  for (int i = 0; i < 7; ++i) {  //  Тесты %s с флагом ширины
    char d1[100] = {0}, d2[100] = {0}, d3[100] = {0}, d4[100] = {0},
         d5[100] = {0}, d6[100] = {0};
    char d11[100] = {0}, d12[100] = {0}, d13[100] = {0}, d14[100] = {0},
         d15[100] = {0}, d16[100] = {0};
    int res1 = 0, res2 = 0;

    res1 = sscanf(str[i], "  %2s %*s %11s %*s %22s %*s %44s %*s %66s %*s %99s ",
                  d1, d2, d3, d4, d5, d6);
    res2 = s21_sscanf(str[i],
                      "  %2s %*s %11s %*s %22s %*s %44s %*s %66s %*s %99s ",
                      d11, d12, d13, d14, d15, d16);
    ck_assert_str_eq(d1,
                     d11);  // Тесты записываемого значения %s с флагом ширины
    ck_assert_str_eq(d2, d12);
    ck_assert_str_eq(d3, d13);
    ck_assert_str_eq(d4, d14);
    ck_assert_str_eq(d5, d15);
    ck_assert_str_eq(d6, d16);
    ck_assert_msg(res1 == res2, "test res width %%s %d",
                  i);  // Тест возвращаемого значения %s с флагом ширины
  }
  for (int i = 0; i < 7; ++i) {  //  Тесты %c без флагов
    char d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0;
    char d11 = 0, d12 = 0, d13 = 0, d14 = 0, d15 = 0, d16 = 0;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str[i], " %c %c%c%c%c%c", &d1, &d2, &d3, &d4, &d5, &d6);
    res2 = s21_sscanf(str[i], " %c %c%c%c%c%c", &d11, &d12, &d13, &d14, &d15,
                      &d16);
    ck_assert_msg(d1 == d11, "test1 %%c %d",
                  i);  // Тесты записываемого значения %c без флагов
    ck_assert_msg(d2 == d12, "test2 %%c %d", i);
    ck_assert_msg(d3 == d13, "test3 %%c %d", i);
    ck_assert_msg(d4 == d14, "test4 %%c %d", i);
    ck_assert_msg(d5 == d15, "test5 %%c %d", i);
    ck_assert_msg(d6 == d16, "test6 %%c %d", i);
    ck_assert_msg(res1 == res2, "test7 res %%с %d",
                  i);  // Тест возвращаемого значения %c без флагов
  }
  for (int i = 0; i < 7; ++i) {  //  Тесты %c с флагом ширины
    char d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0;
    char d11 = 0, d12 = 0, d13 = 0, d14 = 0, d15 = 0, d16 = 0;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str[i], " %1c%*c %2c%*c%3c%*c%c%*c%c%*c%c%*c", &d1, &d2, &d3,
                  &d4, &d5, &d6);
    res2 = s21_sscanf(str[i], " %1c%*c %2c%*c%3c%*c%c%*c%c%*c%c%*c", &d11, &d12,
                      &d13, &d14, &d15, &d16);
    ck_assert_msg(d1 == d11, "test1 %%c %d",
                  i);  // Тесты записываемого значения %c с флагом ширины
    ck_assert_msg(d2 == d12, "test2 %%c %d", i);
    ck_assert_msg(d3 == d13, "test3 %%c %d", i);
    ck_assert_msg(d4 == d14, "test4 %%c %d", i);
    ck_assert_msg(d5 == d15, "test5 %%c %d", i);
    ck_assert_msg(d6 == d16, "test6 %%c %d", i);
    ck_assert_msg(res1 == res2, "test res width %%c %d",
                  i);  // Тест возвращаемого значения %c с флагом ширины
  }
}
END_TEST

START_TEST(SSCANF_N) {  // Тесты %n
  char* str[] = {
      " 23424 122.4325 0x3f 0777 8oO6B1 E()qo@>N&;} h!]H(xIR|yA", "",
      "123456489 12.1234506 4d 023 qweewq qwe w",
      "17976931348623157081452742373170435679807056752584499659891747680315"
      "72607800285387605895586327668781715404589535143824642343213268894641"
      "82768467546703537516986049910576551282076245490090389328944075868508"
      "45513394230458323690322294816580855933212334827479782620414472316873"
      "8177180919299881250404026184124858369.000000 "
      "-1797693134862315708145274237317043567980705675258449965989174768031"
      "57260780028538760589558632766878171540458953514382464234321326889464"
      "18276846754670353751698604991057655128207624549009038932894407586850"
      "84551339423045832369032229481658085593321233482747978262041447231687"
      "38177180919299881250404026184124858369.000000"};
  for (int i = 0; i < 3; ++i) {  //  Тесты %n и мультифлаговости
    int n1 = 0, n2 = 0, n3 = 0, n4 = 0, n5 = 0, n6 = 0, n7 = 0, n8 = 0;
    int n11 = 0, n12 = 0, n13 = 0, n14 = 0, n15 = 0, n16 = 0, n17 = 0, n18 = 0;
    int d1 = 0, d11 = 0, x1 = 0, x11 = 0, o1 = 0, o11 = 0, res1 = 0, res2 = 0;
    float f1 = 0, f11 = 0;
    char str1[50] = {0}, str11[50] = {0};
    char c1 = 0, c2 = 0, c11 = 0, c12 = 0;
    res1 = sscanf(str[i], "%4d %n %8f%n %4x%n %1o%n %s%n %*c%n %4c%n %c%n", &d1,
                  &n1, &f1, &n2, &x1, &n3, &o1, &n4, str1, &n5, &n6, &c1, &n7,
                  &c2, &n8);
    res2 = s21_sscanf(str[i], "%4d %n %8f%n %4x%n %1o%n %s%n %*c%n %4c%n %c%n",
                      &d11, &n11, &f11, &n12, &x11, &n13, &o11, &n14, str11,
                      &n15, &n16, &c11, &n17, &c12, &n18);
    ck_assert_msg(n1 == n11, "test mult1 %%n %d",
                  i);  // Тесты записываемого значения %n
    ck_assert_msg(n2 == n12, "test2 %%n %d", i);
    ck_assert_msg(n3 == n13, "test3 %%n %d", i);
    ck_assert_msg(n4 == n14, "test4 %%n %d", i);
    ck_assert_msg(n5 == n15, "test5 %%n %d", i);
    ck_assert_msg(n6 == n16, "test6 %%n %d", i);
    ck_assert_msg(n7 == n17, "test7 %%n %d", i);
    ck_assert_msg(n8 == n18, "test8 %%n %d", i);
    ck_assert_msg(d1 == d11, "test1 multiflags %d", i);
    ck_assert_msg(f1 == f11, "test2 multiflags %%n %d", i);
    ck_assert_msg(x1 == x11, "test3 multiflags %%n %d", i);
    ck_assert_msg(o1 == o11, "test4 multiflags %%n %d", i);
    ck_assert_str_eq(str1, str11);
    ck_assert_int_eq(c1, c11);
    ck_assert_msg(c2 == c12, "test6 multiflags %%n %d", i);
    ck_assert_msg(res1 == res2, "test multiflags+%%n %d",
                  i);  // Тест возвращаемого значения %n
  }
  long double lf1 = 0, lf11 = 0;
  int n1 = 0, n11 = 0, res1 = 0, res2 = 0;
  res1 = sscanf(str[3], "%Lf%n", &lf1, &n1);
  res2 = s21_sscanf(str[3], "%Lf%n", &lf11, &n11);
  ck_assert_msg(n1 == n11, "test long value %%n %d",
                3);  // Тест записываемого значения %n при чтении
                     // спецификатора с флагом длины
  ck_assert_msg(res1 == res2, "test res long value %%n %d",
                3);  // Тест возвращаемого значения %n при чтении
                     // спецификатора с флагом длины
  do {  // - //тест на запись %n
    char* str5 = "123456489 12.1234506 4d 023";
    int q2 = 0, q4 = 0, q7 = 0, q9 = 0;
    float q3 = 0;
    int q1 = 0, q6 = 0, q8 = 0;
    int res1 = 0, res2 = 0;
    res1 = sscanf(str5, "%6d%n %6f%n %1x%n %2o%n", &q1, &q2, &q3, &q4, &q6, &q7,
                  &q8, &q9);
    int q12 = 0, q14 = 0, q17 = 0, q19 = 0;
    float q13 = 0;
    int q11 = 0, q16 = 0, q18 = 0;
    res2 = s21_sscanf(str5, "%6d%n %6f%n %1x%n %2o%n", &q11, &q12, &q13, &q14,
                      &q16, &q17, &q18, &q19);
    ck_assert_msg(q1 == q11, "test11 %%n");
    ck_assert_msg(q2 == q12, "test12 %%n");
    ck_assert_msg(q3 == q13, "test13 %%n");
    ck_assert_msg(q4 == q14, "test14 %%n");
    ck_assert_msg(q6 == q16, "test16 %%n");
    ck_assert_msg(q7 == q17, "test17 %%n");
    ck_assert_msg(q8 == q18, "test18 %%n");
    ck_assert_msg(q9 == q19, "test19 %%n");
    ck_assert_msg(res1 == res2, "test11 res %%n");
  } while (0);
}
END_TEST

START_TEST(SSCANF_PROCENT) {  // Тест %% и поведения, если строка ввода и строка
                              // формата идентичны
  char* str[] = {
      " Q:zWfQm $its_a_me% %qweewq Mario Q:%zqWsadQ`1234my oNgSXp "
      "Tmn%%|(ZaQ%%H=hY8oO6B1E()qo@>N&;}",
      ""};
  for (int i = 0; i < 2; ++i) {  // Тест %% и поведения, если строка ввода и
                                 // строка формата идентичны
    char d1[100] = {0};
    char d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0;
    char d11[100] = {0};
    char d12 = 0, d13 = 0, d14 = 0, d15 = 0, d16 = 0;
    int res1 = 0, res2 = 0;
    res1 = sscanf(
        str[i], " %s $its_a_me%% %%%*s Mario %c%*c%%%*c q %c sad %c `1234 %c%c",
        d1, &d2, &d3, &d4, &d5, &d6);
    res2 = s21_sscanf(
        str[i],
        "  %s $its_a_me%% %%%*s Mario %c%*c%%%*c q %c sad %c `1234 %c%c%z", d11,
        &d12, &d13, &d14, &d15, &d16);
    ck_assert_str_eq(d1, d11);
    ck_assert_msg(d2 == d12, "test2 %%%% %d",
                  2);  // Тесты записываемого значения
    ck_assert_msg(d3 == d13, "test3 %%%% %d", 3);
    ck_assert_msg(d4 == d14, "test4 %%%% %d", 4);
    ck_assert_msg(d5 == d15, "test5 %%%% %d", 5);
    ck_assert_msg(d6 == d16, "test6 %%%% %d", 6);
    ck_assert_msg(res1 == res2, "test %%%% %d",
                  7);  // Тест возвращаемого значения
  }
}
END_TEST

START_TEST(S21_SPRINTF) {
  char buffer1[500] = {0};
  char buffer2[500] = {0};
  int a = 9999;
  int b = 1;
  int plus = +9;
  int minus = -8;
  char c = 'A';
  float f = 3.14;
  unsigned int u = 12345;
  long int la = +9223372036854775807L;
  long int lb = -9223372036854775807L;
  short int ha = +32767;
  short int hb = -32767;
  unsigned long int ula = +1844674407370955161UL;
  unsigned long int ulb = 1844674407370955161UL;
  unsigned short int uha = +32767U;
  unsigned short int uhb = 32767U;

  ck_assert_msg(s21_sprintf(buffer1, "Sum of %d and %d is %d", a, b, a + b) ==
                    sprintf(buffer2, "Sum of %d and %d is %d", a, b, a + b),
                "Fail test 1");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "Num with plus: %d, Num with minus %d", plus,
                  minus) ==
          sprintf(buffer2, "Num with plus: %d, Num with minus %d", plus, minus),
      "Fail test 2");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "Num with plus: %+d, Num with minus %d",
                            plus, minus) ==
                    sprintf(buffer2, "Num with plus: %+d, Num with minus %d",
                            plus, minus),
                "Fail test 3");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "Num with plus: % d, Num with minus %d",
                            plus, minus) ==
                    sprintf(buffer2, "Num with plus: % d, Num with minus %d",
                            plus, minus),
                "Fail test 4");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "%-9d", 38) == sprintf(buffer2, "%-9d", 38),
      "Fail test 5");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "%-5d", 38) == sprintf(buffer2, "%-5d", 38),
      "Fail test 6");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "%-9s", "Tom") == sprintf(buffer2, "%-9s", "Tom"),
      "Fail test 7");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "Letter: %-9c", c) ==
                    sprintf(buffer2, "Letter: %-9c", c),
                "Fail test 8");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "%-9u", u) == sprintf(buffer2, "%-9u", u),
                "Fail test 9");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "%9d", 38) == sprintf(buffer2, "%9d", 38),
                "Fail test 10");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "%5u", 38) == sprintf(buffer2, "%5u", 38),
                "Fail test 11");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "%9s", "Tom") == sprintf(buffer2, "%9s", "Tom"),
      "Fail test 12");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "Letter: %9c", c) ==
                    sprintf(buffer2, "Letter: %9c", c),
                "Fail test 13");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "%9u", u) == sprintf(buffer2, "%9u", u),
                "Fail test 14");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "Sum of %d and %d is %d", a, b, a + b) ==
                    sprintf(buffer2, "Sum of %d and %d is %d", a, b, a + b),
                "Fail test 15");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "Letter: %c", c) ==
                    sprintf(buffer2, "Letter: %c", c),
                "Fail test 16");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "%s", "Hello world!") ==
                    sprintf(buffer2, "%s", "Hello world!"),
                "Fail test 17");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "%u", u) == sprintf(buffer2, "%u", u),
                "Fail test 18");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "%%") == sprintf(buffer2, "%%"),
                "Fail test 19");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "%9f", f) == sprintf(buffer2, "%9f", f),
                "Fail test 20");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "%9.8f", f) == sprintf(buffer2, "%9.8f", f),
      "Fail test 21");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "%-9f", f) == sprintf(buffer2, "%-9f", f),
                "Fail test 22");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "Float number %f", f) ==
                    sprintf(buffer2, "Float number %f", f),
                "Fail test 23");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "Float number %f", 3.145) ==
                    sprintf(buffer2, "Float number %f", 3.145),
                "Fail test 24");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "Float number %f", 2.10) ==
                    sprintf(buffer2, "Float number %f", 2.10),
                "Fail test 25");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "Float number %f", -2.10) ==
                    sprintf(buffer2, "Float number %f", -2.10),
                "Fail test 26");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "Float number %.4f", f) ==
                    sprintf(buffer2, "Float number %.4f", f),
                "Fail test 27");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "Num with plus: %ld, Num with minus %ld", la, lb) ==
          sprintf(buffer2, "Num with plus: %ld, Num with minus %ld", la, lb),
      "Fail test 28");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "Num with plus: %hd, Num with minus %hd", ha, hb) ==
          sprintf(buffer2, "Num with plus: %hd, Num with minus %hd", ha, hb),
      "Fail test 29");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "Num with plus: %9ld, Num with minus %9ld", la,
                  lb) ==
          sprintf(buffer2, "Num with plus: %9ld, Num with minus %9ld", la, lb),
      "Fail test 30");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "Num with plus: %9hd, Num with minus %9hd", ha,
                  hb) ==
          sprintf(buffer2, "Num with plus: %9hd, Num with minus %9hd", ha, hb),
      "Fail test 31");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "Num with plus: %-9ld, Num with minus %-9ld", la,
                  lb) == sprintf(buffer2,
                                 "Num with plus: %-9ld, Num with minus %-9ld",
                                 la, lb),
      "Fail test 32");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "Num with plus: %-9hd, Num with minus %-9hd", ha,
                  hb) == sprintf(buffer2,
                                 "Num with plus: %-9hd, Num with minus %-9hd",
                                 ha, hb),
      "Fail test 33");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "Num with plus: %lu, Num with minus %lu", ula,
                  ulb) ==
          sprintf(buffer2, "Num with plus: %lu, Num with minus %lu", ula, ulb),
      "Fail test 34");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "Num with plus: %hu, Num with minus %hu", uha,
                  uhb) ==
          sprintf(buffer2, "Num with plus: %hu, Num with minus %hu", uha, uhb),
      "Fail test 35");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "Num with plus: %9lu, Num with minus %9lu",
                            ula, ulb) ==
                    sprintf(buffer2, "Num with plus: %9lu, Num with minus %9lu",
                            ula, ulb),
                "Fail test 36");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(s21_sprintf(buffer1, "Num with plus: %9hu, Num with minus %9hu",
                            uha, uhb) ==
                    sprintf(buffer2, "Num with plus: %9hu, Num with minus %9hu",
                            uha, uhb),
                "Fail test 37");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "Num with plus: %-9lu, Num with minus %-9lu", ula,
                  ulb) == sprintf(buffer2,
                                  "Num with plus: %-9lu, Num with minus %-9lu",
                                  ula, ulb),
      "Fail test 38");
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_msg(
      s21_sprintf(buffer1, "Num with plus: %-9hd, Num with minus %-9hd", uha,
                  uhb) == sprintf(buffer2,
                                  "Num with plus: %-9hd, Num with minus %-9hd",
                                  uha, uhb),
      "Fail test 39");
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

START_TEST(SPRINTF_C) {
  do {
    char str1[100];
    char str2[100];
    char* str3 = "%c Test %c Test %c Test %c Test %c";
    int a = 'a';
    int b = 'b';
    int c = '\0';
    int d = 'D';
    int e = 'e';
    int res1 = sprintf(str1, str3, a, b, c, d, e);
    int res2 = s21_sprintf(str2, str3, a, b, c, d, e);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%lc Test % c Test %c Test % c Test %c";
    int a = 'A';
    int b = 'B';
    int c = 'C';
    int d = 'D';
    int e = 'E';
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%+c Test %-c Test %0c Test %+-c Test %-+c";
    int a = 'A';
    int b = 'B';
    int c = 'C';
    int d = 'D';
    int e = 'E';
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%0 c Test %+ c Test %- c Test %+- c Test %-+ c";
    int a = 'A';
    int b = 'B';
    int c = 'C';
    int d = 'D';
    int e = 'E';
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "Test %c Test %c Test %03c Test %03c";
    int b = 'B';
    int c = 'C';
    int d = 'D';
    int e = 'E';
    int res1 = sprintf(str1, str3, b, c, d, e);
    int res2 = s21_sprintf(str2, str3, b, c, d, e);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%-03c Test % -3c Test %-lc";
    int a = 74;
    unsigned long int b = 74;
    int res1 = sprintf(str1, str3, a, a, b);
    int res2 = s21_sprintf(str2, str3, a, a, b);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%2.3c Test %-2.3c Test %2.10lc Test %-2.10lc Test %-0lc";
    int a = 10;
    unsigned long int b = 10;
    unsigned long int c = 10;
    ck_assert_int_eq(sprintf(str1, str3, a, a, b, c, c),
                     s21_sprintf(str2, str3, a, a, b, c, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%2.3c Test %-2.3c Test %2.10lc Test %-2.10lc Test %-0lc";
    int a = -10;
    unsigned long int b = 10;
    unsigned long int c = 10;
    ck_assert_int_eq(sprintf(str1, str3, a, a, b, c, c),
                     s21_sprintf(str2, str3, a, a, b, c, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%c Test %c Test %c Test %c Test %c";
    int res1 = sprintf(str1, str3, '\n', '\0', '\0', '\0', 'c');
    int res2 = s21_sprintf(str2, str3, '\n', '\0', '\0', '\0', 'c');
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "%.5c Test %-5c Test %-0c Test % 05c Test %0c";
    int a = 45;
    ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a),
                     s21_sprintf(str2, str3, a, a, a, a, a));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "%5c Test %-5c Test %05c Test %-05c Test %- 5c";
    int a = 255;
    ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a),
                     s21_sprintf(str2, str3, a, a, a, a, a));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%c Test %c Test %c Test %c Test %c";
    char a = '\0';
    int res1 = sprintf(str1, str3, a, a, a, a, a);
    int res2 = s21_sprintf(str2, str3, a, a, a, a, a);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%c Test %c Test %c Test %c Test %c";
    int res1 = sprintf(str1, str3, 'b', '4', '#', '@', '\0');
    int res2 = s21_sprintf(str2, str3, 'b', '4', '#', '@', '\0');
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%c Test %c Test %c Test %c Test %c";
    int res1 = sprintf(str1, str3, 'Y', '\0', 'G', 123, 'J');
    int res2 = s21_sprintf(str2, str3, 'Y', '\0', 'G', 123, 'J');
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
  } while (0);
}
END_TEST

START_TEST(SPRINTF_S) {
  do {
    char str1[100] = "";
    char str2[100] = "";
    char* str3 = "Test %s Test";
    char* a = "Why am I here?!";
    ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%s Test %s Test %s";
    char* a = "I'm so tired";
    char* b = "Who invented this?";
    char* c = "This project gave me hemmoroids";
    ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                     s21_sprintf(str2, str3, a, b, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%+s Test %-s Test %.s";
    char* a = "Don't need this test";
    char* b = "Just for the kicks";
    char* c = "Lol";
    ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                     s21_sprintf(str2, str3, a, b, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%3s Test %5s Test %-10s";
    char* a = "WHAT IS THIS";
    char* b = "i don't care anymore";
    char* c = "PPAP";

    ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                     s21_sprintf(str2, str3, a, b, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%6.5s Test %.23s Test %3.s TEST %.s";
    char* a = "WHAT IS THIS";
    char* b = "i don't care anymore, really";
    char* c = "PPAP";
    char* d = "I don't feel so good";

    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                     s21_sprintf(str2, str3, a, b, c, d));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%-10.5s Test %-.8s Test %-7s TEST %-.s";
    char* a = "WHAT IS THIS";
    char* b = "i don't care anymore, really";
    char* c = "PPAP";
    char* d = "I don't feel so good";
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                     s21_sprintf(str2, str3, a, b, c, d));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%0s Test %0.s Test %0.0s TEST %0s GOD %.s";
    char* a = "WHAT IS THIS";
    char* b = "i don't care anymore, really";
    char* c = "PPAP";
    char* d = "I don't feel so good";
    char* e = "What is lovin'?!";
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%+s Test %+3.s Test %5.7s TEST %10s";
    char* a = "WHAT IS THIS";
    char* b = "i don't care anymore, really";
    char* c = "abcd";
    char* d = "I don't feel so good";
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                     s21_sprintf(str2, str3, a, b, c, d));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "% s Test % 3.s Test % 5.7s TEST % 10s GOD %.s";
    char* a = "WHAT IS THIS";
    char* b = "i don't care anymore, really";
    char* c = "PPAP";
    char* d = "I don't feel so good";
    char* e = "What is lovin'?!";

    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%+s Test %+3.s Test %+5.7s TEST %10s GOD %+.s";
    char* a = "\0";
    char* b = "\0";
    char* c = "\0";
    char* d = "\0";
    char* e = "\0";
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%s %s %s %% %d";
    char* a = "This";
    char* b = "\0";
    int c = 65;
    char* d = "string";
    ck_assert_int_eq(sprintf(str1, str3, a, b, d, c),
                     s21_sprintf(str2, str3, a, b, d, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%4.8s TesT %-4.8s";
    char* a = "WHAT IS THIS";
    int res1 = sprintf(str1, str3, a, a);
    int res2 = s21_sprintf(str2, str3, a, a);
    ck_assert_int_eq(res1, res2);
    ck_assert_pstr_eq(str1, str2);
  } while (0);
  do {
    char str1[200];
    char str2[200];
    char* str3 = "%8.s TesT %-8.s";
    char* a = "WHAT IS THIS";
    int res1 = sprintf(str1, str3, a, a);
    int res2 = s21_sprintf(str2, str3, a, a);
    ck_assert_int_eq(res1, res2);
    ck_assert_pstr_eq(str1, str2);
  } while (0);
  do {
    char str1[200];
    char str2[200];
    char* str3 = "%8.4s TesT %-8.4s";
    char* a = "WHAT IS THIS";
    int res1 = sprintf(str1, str3, a, a);
    int res2 = s21_sprintf(str2, str3, a, a);
    ck_assert_int_eq(res1, res2);
    ck_assert_pstr_eq(str1, str2);
  } while (0);
  do {
    char str1[200];
    char str2[200];
    char* str3 = "%-16.0s TesT %-16.0s";
    char* a = "WHAT IS THIS";
    int res1 = sprintf(str1, str3, a, a);
    int res2 = s21_sprintf(str2, str3, a, a);
    ck_assert_int_eq(res1, res2);
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%4.4s TesT %-4.4s";
    char* a = "WHAT IS THIS";
    int res1 = sprintf(str1, str3, a, a);
    int res2 = s21_sprintf(str2, str3, a, a);
    ck_assert_int_eq(res1, res2);
    ck_assert_pstr_eq(str1, str2);
  } while (0);
  do {
    char str1[200];
    char str2[200];
    char* str3 = "%+8s TesT %-8s";
    char* a = "WHAT IS THIS";
    int res1 = sprintf(str1, str3, a, a);
    int res2 = s21_sprintf(str2, str3, a, a);
    ck_assert_int_eq(res1, res2);
    ck_assert_pstr_eq(str1, str2);
  } while (0);
  do {
    char str1[200];
    char str2[200];
    char* str3 = "%08.s TesT %-08.s";
    char* a = "WHAT IS THIS";
    int res1 = sprintf(str1, str3, a, a);
    int res2 = s21_sprintf(str2, str3, a, a);
    ck_assert_int_eq(res1, res2);
    ck_assert_pstr_eq(str1, str2);
  } while (0);
  do {
    char str1[200];
    char str2[200];
    char* str3 = "%-016.4s TesT %016.4s";
    char* a = "WHAT IS THIS";
    int res1 = sprintf(str1, str3, a, a);
    int res2 = s21_sprintf(str2, str3, a, a);
    ck_assert_int_eq(res1, res2);
    ck_assert_pstr_eq(str1, str2);
  } while (0);
  do {
    char str1[200];
    char str2[200];
    char* str3 = "%08.s TesT %-08.s";
    char* a = "WHAT IS THIS";
    int res1 = sprintf(str1, str3, a, a);
    int res2 = s21_sprintf(str2, str3, a, a);
    ck_assert_int_eq(res1, res2);
    ck_assert_pstr_eq(str1, str2);
  } while (0);
  do {
    char str1[200];
    char str2[200];
    char* str3 = "%-012.16s TesT %012.16s";
    char* a = "WHAT IS THIS";
    int res1 = sprintf(str1, str3, a, a);
    int res2 = s21_sprintf(str2, str3, a, a);
    ck_assert_int_eq(res1, res2);
    ck_assert_pstr_eq(str1, str2);
  } while (0);
}
END_TEST

START_TEST(SPRINTF_D) {
  do {
    char str1[100];
    char str2[100];
    char* str3 = "%d Test %d Test %d";
    int a = -2147483647;
    int b = 0;
    int c = 2147483647;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                     s21_sprintf(str2, str3, a, b, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%+d Test %+d Test %+d";
    int a = -2147483647;
    int b = 0;
    int c = 2147483647;

    ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                     s21_sprintf(str2, str3, a, b, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%-2d Test %-2d Test %-2d";
    int a = -2147483647;
    int b = 0;
    int c = 2147483647;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                     s21_sprintf(str2, str3, a, b, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%ld Test %ld Test %hd GOD %hd";
    long int a = 3088675747373646;
    long b = 33030030303;
    short int c = 22600;
    short d = -120;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                     s21_sprintf(str2, str3, a, b, c, d));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%3d Test %5d Test %10d";
    int a = -3015;
    ck_assert_int_eq(sprintf(str1, str3, a, a, a),
                     s21_sprintf(str2, str3, a, a, a));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%6.5d Test %.23d Test %3.d TEST %.d %.6d";
    int a = -3015;
    int b = -712;
    int c = -99;
    int d = -38;
    int e = -100;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%-9.6d Test %-0.8d Test %-7d TEST %-.d";
    int a = -3015;
    int b = -712;
    int c = -99;
    int d = -2939;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                     s21_sprintf(str2, str3, a, b, c, d));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "% d Test % 3.d Test % 5.7d TEST % 10d GOD %.d";
    int a = -32;
    int b = -8899;
    int c = -91918;
    int d = -32311;
    int e = -23;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%+d Test %+3.d Test %+5.7d TEST %+10d GOD %+.d";
    int a = -32;
    int b = -8899;
    int c = 91918;
    int d = -32311;
    int e = 3261;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);
}
END_TEST

START_TEST(SPRINTF_LD) {
  do {
    char str1[100];
    char str2[100];
    char* str3 = "%ld Test %ld Test %ld";
    long int a = -2147483647;
    long int b = 0;
    long int c = 2147483647;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                     s21_sprintf(str2, str3, a, b, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%+ld Test %+ld Test %+ld";
    long int a = -2147483647;
    long int b = 0;
    long int c = 2147483647;

    ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                     s21_sprintf(str2, str3, a, b, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%-2ld Test %-2ld Test %-2ld";
    long int a = -2147483647;
    long int b = 0;
    long int c = 2147483647;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                     s21_sprintf(str2, str3, a, b, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "% ld Test %ld Test % hd GOD %hd";
    long int a = 3088675747373646;
    long b = 33030030303;
    short int c = 22600;
    short d = -120;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                     s21_sprintf(str2, str3, a, b, c, d));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%3ld Test %5ld Test %10ld";
    long int a = -3015;
    ck_assert_int_eq(sprintf(str1, str3, a, a, a),
                     s21_sprintf(str2, str3, a, a, a));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%6.5ld Test %.23ld Test %3.ld TEST %.ld %.6ld";
    long int a = -3015;
    long int b = -712;
    long int c = -99;
    long int d = -38;
    long int e = -100;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%-9.6ld Test %-0.8ld Test %-7ld TEST %-.ld";
    long int a = -3015;
    long int b = -712;
    long int c = -99;
    long int d = -2939;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                     s21_sprintf(str2, str3, a, b, c, d));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "% ld Test % 3.ld Test % 5.7ld TEST % 10ld GOD %.ld";
    long int a = -32;
    long int b = -8899;
    long int c = -91918;
    long int d = -32311;
    long int e = -23;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%+ld Test %+3.ld Test %+5.7ld TEST %+10ld GOD %+.ld";
    long int a = -32;
    long int b = -8899;
    long int c = 91918;
    long int d = -32311;
    long int e = 3261;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);
}
END_TEST

START_TEST(SPRINTF_U) {
  do {
    char str1[100];
    char str2[100];
    char* str3 = "%u Test %u Test %u";
    unsigned int a = -2147483647;
    unsigned int b = 0;
    unsigned int c = 2147483647;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                     s21_sprintf(str2, str3, a, b, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%+u Test %+u Test %+u";
    unsigned int a = -2147483647;
    unsigned int b = 0;
    unsigned int c = 2147483647;

    ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                     s21_sprintf(str2, str3, a, b, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%-2u Test %-2u Test %-2u";
    unsigned int a = -2147483647;
    unsigned int b = 0;
    unsigned int c = 2147483647;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                     s21_sprintf(str2, str3, a, b, c));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%lu Test %lu Test %hu GOD %hu";
    unsigned long int a = 3088675747373646;
    unsigned long b = 33030030303;
    unsigned short int c = 22600;
    unsigned short d = -120;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                     s21_sprintf(str2, str3, a, b, c, d));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[100];
    char str2[100];
    char* str3 = "%3d Test %5u Test %10u";
    unsigned int a = -3015;
    ck_assert_int_eq(sprintf(str1, str3, a, a, a),
                     s21_sprintf(str2, str3, a, a, a));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%6.5u Test %.23u Test %3.u TEST %.d %.6u";
    unsigned int a = -3015;
    unsigned int b = -712;
    unsigned int c = -99;
    unsigned int d = -38;
    int e = -100;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%-9.6u Test %-0.8u Test %-7u TEST %-.u";
    unsigned int a = -3015;
    unsigned int b = -712;
    unsigned int c = -99;
    unsigned int d = -2939;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                     s21_sprintf(str2, str3, a, b, c, d));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "% u Test % 3.u Test % 5.7u TEST % 10u GOD %.u";
    unsigned int a = -32;
    unsigned int b = -8899;
    unsigned int c = -91918;
    unsigned int d = -32311;
    unsigned int e = -23;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%+u Test %+3.u Test %+5.7u TEST %+10u GOD %+.u";
    unsigned int a = -32;
    unsigned int b = -8899;
    unsigned int c = 91918;
    unsigned int d = -32311;
    unsigned int e = 3261;
    ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                     s21_sprintf(str2, str3, a, b, c, d, e));
    ck_assert_pstr_eq(str1, str2);
  } while (0);
}
END_TEST

START_TEST(sprintf_1_u) {
  char str1[100] = "";
  char str2[100] = "";
  char* str3 = "Test %u Test";
  unsigned int a = 012;
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_u) {
  char str1[100];
  char str2[100];
  char* str3 = "%u Test %u Test %u";
  unsigned int a = 012;
  unsigned int b = 017;
  unsigned int c = 07464;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                   s21_sprintf(str2, str3, a, b, c));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_u) {
  char str1[100];
  char str2[100];
  char* str3 = "%-u Test %-u Test %-u";
  unsigned int a = 3015;
  unsigned int b = 712;
  unsigned int c = 99;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                   s21_sprintf(str2, str3, a, b, c));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_u) {
  char str1[100];
  char str2[100];
  char* str3 = "%lu Test %lu Test %hu GOD %hu";
  long unsigned int a = 3088675747373646;
  long unsigned b = 33030030303;
  unsigned short c = 22600;
  unsigned short d = 120;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                   s21_sprintf(str2, str3, a, b, c, d));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_u) {
  char str1[100];
  char str2[100];
  char* str3 = "%03d Test % 05d Test %10.11d";
  unsigned int a = 3015;
  unsigned int b = 01234;
  unsigned int c = 99;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                   s21_sprintf(str2, str3, a, b, c));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_u) {
  char str1[200];
  char str2[200];
  char* str3 = "%.2u Test %.4u Test %0.3u TEST %.u";
  unsigned int a = 3015;
  unsigned int b = 712;
  unsigned int c = 99;
  unsigned int d = 38;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                   s21_sprintf(str2, str3, a, b, c, d));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_7_u) {
  char str1[200];
  char str2[200];
  char* str3 = "%-10.5u Test %-.8u Test %-7u TEST %-.u";
  unsigned int a = 3015;
  unsigned int b = 712;
  unsigned int c = 99;
  unsigned int d = 2939;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                   s21_sprintf(str2, str3, a, b, c, d));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_8_u) {
  char str1[200];
  char str2[200];
  char* str3 = "%0u Test %0.u Test %0.0u TEST %0u GOD %.u";
  unsigned int a = 3015;
  unsigned int b = 712;
  unsigned int c = 99;
  unsigned int d = 2939;
  unsigned int e = 0123;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_9_u) {
  char str1[200];
  char str2[200];
  char* str3 = "%u Test %3.u Test %5.7u TEST %10u";
  unsigned int a = 3015;
  unsigned int b = 712;
  unsigned int c = 99;
  unsigned int d = 2939;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                   s21_sprintf(str2, str3, a, b, c, d));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_u) {
  char str1[200];
  char str2[200];
  char* str3 = "%u Test %3.u Test %5.7u TEST %10u GOD %.u";
  unsigned int a = 32;
  unsigned int b = 8899;
  unsigned int c = 91918;
  unsigned int d = 32311;
  unsigned int e = 23;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_12_u) {
  char str1[200];
  char str2[200];
  char* str3 = "%u Test %3.u Test %5.7u TEST %10u GOD %.u";
  unsigned int a = 32;
  unsigned int b = 8899;
  unsigned int c = 91918;
  unsigned int d = 32311;
  unsigned int e = 3261;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_17_u) {
  char str1[200];
  char str2[200];
  char* str3 = "%- u Test %-15u sdasda %-15u sdsad %-u";
  unsigned int a = -3231;
  unsigned int b = -3231;
  unsigned int c = 3231;
  unsigned int d = 3231;

  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                   s21_sprintf(str2, str3, a, b, c, d));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_18_u) {
  char str1[100] = "test";
  char str2[100] = "test";
  char format_str[100] = "test%06.3d!test%5.d!";
  int u = 55;
  int res1 = sprintf(str1, format_str, u, u);
  int res2 = s21_sprintf(str2, format_str, u, u);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_19_u) {
  char str1[200];
  char str2[200];
  char* str3 = "%+u Test %+3.u Test %+5.7u TEST %+10u";
  unsigned int a = 3015;
  unsigned int b = 712;
  unsigned int c = 99;
  unsigned int d = 2939;
  int res1 = sprintf(str1, str3, a, b, c, d);
  int res2 = s21_sprintf(str2, str3, a, b, c, d);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_20_u) {
  char str1[200];
  char str2[200];
  char* str3 = "% d Test % 3.d Test % 5.7d TEST % 10d GOD %.d";
  unsigned int a = 32;
  unsigned int b = 8899;
  unsigned int c = 91918;
  unsigned int d = 32311;
  unsigned int e = 23;
  int res1 = sprintf(str1, str3, a, b, c, d, e);
  int res2 = s21_sprintf(str2, str3, a, b, c, d, e);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_21_u) {
  char str1[200];
  char str2[200];
  char* str3 = "%+u Test %+3.u Test %+5.7u TEST %+10u GOD %+.u";
  unsigned int a = 32;
  unsigned int b = 8899;
  unsigned int c = 91918;
  unsigned int d = 32311;
  unsigned int e = 3261;
  int res1 = sprintf(str1, str3, a, b, c, d, e);
  int res2 = s21_sprintf(str2, str3, a, b, c, d, e);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_1_lu) {
  char str1[100] = "";
  char str2[100] = "";
  char* str3 = "Test %lu Test";
  unsigned long int a = 012;
  ck_assert_int_eq(sprintf(str1, str3, a), s21_sprintf(str2, str3, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_lu) {
  char str1[100];
  char str2[100];
  char* str3 = "%- lu Test %  lu Test %   lu";
  unsigned long int a = 012;
  unsigned long int b = 017;
  unsigned long int c = 07464;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                   s21_sprintf(str2, str3, a, b, c));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_lu) {
  char str1[100];
  char str2[100];
  char* str3 = "%-lu Test %-lu Test %-lu";
  unsigned long int a = 3015;
  unsigned long int b = 712;
  unsigned long int c = 99;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                   s21_sprintf(str2, str3, a, b, c));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_lu) {
  char str1[100];
  char str2[100];
  char* str3 = "%lu Test % lu Test %hu GOD % hu";
  long unsigned int a = 3088675747373646;
  long unsigned int b = 33030030303;
  unsigned short c = 22600;
  unsigned short d = 120;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                   s21_sprintf(str2, str3, a, b, c, d));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_lu) {
  char str1[100];
  char str2[100];
  char* str3 = "%03lu Test % 05lu Test %10.11lu";
  unsigned long int a = 3015;
  unsigned long int b = 1234;
  unsigned long int c = 99;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c),
                   s21_sprintf(str2, str3, a, b, c));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_lu) {
  char str1[200];
  char str2[200];
  char* str3 = "%.2lu Test %.4lu Test %0.3lu TEST %.lu";
  unsigned long int a = 3015;
  unsigned long int b = 712;
  unsigned long int c = 99;
  unsigned long int d = 38;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                   s21_sprintf(str2, str3, a, b, c, d));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_7_lu) {
  char str1[200];
  char str2[200];
  char* str3 = "%-10.5lu Test %-.8lu Test %-7lu TEST %-.lu";
  unsigned long int a = 3015;
  unsigned long int b = 712;
  unsigned long int c = 99;
  unsigned long int d = 2939;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                   s21_sprintf(str2, str3, a, b, c, d));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_8_lu) {
  char str1[200];
  char str2[200];
  char* str3 = "%0u Test %0.lu Test %0.0lu TEST %0lu GOD %.lu";
  unsigned long int a = 3015;
  unsigned long int b = 712;
  unsigned long int c = 99;
  unsigned long int d = 2939;
  unsigned long int e = 0123;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_9_lu) {
  char str1[200];
  char str2[200];
  char* str3 = "%lu Test %3.lu Test %5.7lu TEST %10lu";
  unsigned long int a = 3015;
  unsigned long int b = 712;
  unsigned long int c = 99;
  unsigned long int d = 2939;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                   s21_sprintf(str2, str3, a, b, c, d));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_lu) {
  char str1[200];
  char str2[200];
  char* str3 = "%lu Test %3.lu Test %5.7lu TEST %10lu GOD %.lu";
  unsigned long int a = 32;
  unsigned long int b = 8899;
  unsigned long int c = 91918;
  unsigned long int d = 32311;
  unsigned long int e = 23;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_12_lu) {
  char str1[200];
  char str2[200];
  char* str3 = "%lu Test %3.lu Test %5.7lu TEST %10lu GOD %.lu";
  unsigned long int a = 32;
  unsigned long int b = 8899;
  unsigned long int c = 91918;
  unsigned long int d = 32311;
  unsigned long int e = 3261;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_17_lu) {
  char str1[200];
  char str2[200];
  char* str3 = "%- lu Test %-15lu sdasda %-15lu sdsad %-lu";
  unsigned long int a = -3231;
  unsigned long int b = -3231;
  unsigned long int c = 3231;
  unsigned long int d = 3231;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d),
                   s21_sprintf(str2, str3, a, b, c, d));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_18_lu) {
  char str1[100] = "test";
  char str2[100] = "test";
  char format_str[100] = "test%06.3lu!test%5.lu!";
  unsigned long int u = 55;
  int res1 = sprintf(str1, format_str, u, u);
  int res2 = s21_sprintf(str2, format_str, u, u);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_19_lu) {
  char str1[200];
  char str2[200];
  char* str3 = "%+lu Test %+3.lu Test %+5.7lu TEST %+10lu";
  unsigned long int a = 3015;
  unsigned long int b = 712;
  unsigned long int c = 99;
  unsigned long int d = 2939;
  int res1 = sprintf(str1, str3, a, b, c, d);
  int res2 = s21_sprintf(str2, str3, a, b, c, d);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_20_lu) {
  char str1[200];
  char str2[200];
  char* str3 = "% d Test % 3.d Test % 5.7d TEST % 10d GOD %.d";
  unsigned long int a = 32;
  unsigned long int b = 8899;
  unsigned long int c = 91918;
  unsigned long int d = 32311;
  unsigned long int e = 3261;
  int res1 = sprintf(str1, str3, a, b, c, d, e);
  int res2 = s21_sprintf(str2, str3, a, b, c, d, e);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_21_lu) {
  char str1[200];
  char str2[200];
  char* str3 = "%+lu Test %+3.lu Test %+5.7lu TEST %+10lu GOD %+.lu";
  unsigned long int a = 32;
  unsigned long int b = 8899;
  unsigned long int c = 91918;
  unsigned long int d = 32311;
  unsigned long int e = 3261;
  int res1 = sprintf(str1, str3, a, b, c, d, e);
  int res2 = s21_sprintf(str2, str3, a, b, c, d, e);
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(SPRINTF_F) {
  do {
    char str1[200];
    char str2[200];
    char* str3 = "%f TEST %.f TEST %4f TEST %4.f TEST %5.0f! TEST %.3f";
    double num = 76.7327;
    sprintf(str1, str3, num, num, num, num, num, num);
    s21_sprintf(str2, str3, num, num, num, num, num, num);
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%f TEST %.f TEST %4f TEST %4.f TEST %5.0f!";
    double num = 76.756589367;
    sprintf(str1, str3, num, num, num, num, num);
    s21_sprintf(str2, str3, num, num, num, num, num);
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[200];
    char str2[200];
    char* str3 = "%4.05f TEST %.05f TEST %05.4f TEST %4.4f TEST %5.10f!";
    double num = -76.756589367;
    ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                     s21_sprintf(str2, str3, num, num, num, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: %025f!  test: %-015f!  test: %+11f!";
    double num = 8364.4366;
    ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                     s21_sprintf(str2, str3, num, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 =
        "test1: %- - +  0 +  + 25.5f!\ntest2: %- 030.4f!\ntest3: %+  016.6f!";
    double num = 837564.4753366;
    int res1 = sprintf(str1, str3, num, num, num);
    int res2 = s21_sprintf(str2, str3, num, num, num);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test1: %015f!\ntest2: %-026f!\ntest3: %+018f!";
    double num = -947.6785643;
    int res1 = sprintf(str1, str3, num, num, num);
    int res2 = s21_sprintf(str2, str3, num, num, num);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: %+- 010.2f!\ntest: %- 025.7f!\ntest: %+- 18.4f!";
    double num = -947.6785643;
    int res1 = sprintf(str1, str3, num, num, num);
    int res2 = s21_sprintf(str2, str3, num, num, num);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: %10.5ftest: %12.4f!";
    double num = 76.756589;
    ck_assert_int_eq(sprintf(str1, str3, num, num),
                     s21_sprintf(str2, str3, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: % + - - +015.1ftest: %16.2ftest: %18.3f!";
    double num = -48938790.756589;
    ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                     s21_sprintf(str2, str3, num, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: %10.4ftest: %25.5f!";
    double num = -48938790.756589;
    ck_assert_int_eq(sprintf(str1, str3, num, num),
                     s21_sprintf(str2, str3, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: %+ 18.0f!test: %+10.f!test: %+25.f!";
    double num = 48938790.756589;
    ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                     s21_sprintf(str2, str3, num, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: %-15.4f!test: %-26.1f!test: %-18.0f!";
    double num = -365289.3462865487;
    ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                     s21_sprintf(str2, str3, num, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: %15.13lf!test: %26.15lf!";
    double num = -365289.34628654873789362746834;
    ck_assert_int_eq(sprintf(str1, str3, num, num),
                     s21_sprintf(str2, str3, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: %18.7f!test: %10.15f!test: %25.15f!";
    double num = -365289.34628654873789362746834;
    ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                     s21_sprintf(str2, str3, num, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: %15.13lf!test: %26.15lf!";
    double num = 365289.34628654873789362746834;
    ck_assert_int_eq(sprintf(str1, str3, num, num),
                     s21_sprintf(str2, str3, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: %18.7f!test: %10.15f!";
    double num = 365289.34628654873789362746834;
    ck_assert_int_eq(sprintf(str1, str3, num, num),
                     s21_sprintf(str2, str3, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: %- 23.14f!test: %+ 25.15f!";
    double num = 365289.346;
    sprintf(str1, str3, num, num);
    s21_sprintf(str2, str3, num, num);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(sprintf(str1, str3, num, num),
                     s21_sprintf(str2, str3, num, num));
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: %+- 14f!test: %+ 10f!test: % +25f!";
    double num = -365789.34;
    ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                     s21_sprintf(str2, str3, num, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: % 15f!test: % -26f!test: %- 18f!";
    double num = -365789.34;
    ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                     s21_sprintf(str2, str3, num, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: % 14f!test: % -27f!test: %- 19f!";
    double num = -365789.34;
    ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                     s21_sprintf(str2, str3, num, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "test: %+- 16f!test: %+ 44f!test: % +35f!";
    double num = 365789.34;

    ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                     s21_sprintf(str2, str3, num, num, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);

  do {
    char str1[400];
    char str2[400];
    char* str3 = "fshgkaljck% 10.12f hgsakul";
    double num = 0.235300;
    ck_assert_int_eq(sprintf(str1, str3, num), s21_sprintf(str2, str3, num));
    ck_assert_pstr_eq(str1, str2);
  } while (0);
}
END_TEST

START_TEST(S21_TO_UPPER) {
  char* result1 = (char*)s21_to_upper("Hello");
  char* result2 = (char*)s21_to_upper("HELLO");
  char* result3 = (char*)s21_to_upper("HeLlO");
  char* result4 = (char*)s21_to_upper("hello123");
  char* result5 = (char*)s21_to_upper("Hello_}(&&*^)");
  ck_assert_str_eq(result1, "HELLO");
  free(result1);
  ck_assert_str_eq(result2, "HELLO");
  free(result2);
  ck_assert_str_eq(result3, "HELLO");
  free(result3);
  ck_assert_str_eq(result4, "HELLO123");
  free(result4);
  ck_assert_str_eq(result5, "HELLO_}(&&*^)");
  free(result5);
}
END_TEST

START_TEST(S21_TO_LOWER) {
  char* result1 = (char*)s21_to_lower("Hello");
  char* result2 = (char*)s21_to_lower("HELLO");
  char* result3 = (char*)s21_to_lower("HeLlO");
  char* result4 = (char*)s21_to_lower("hello123");
  char* result5 = (char*)s21_to_lower("Hello_}(&&*^)");
  ck_assert_str_eq(result1, "hello");
  free(result1);
  ck_assert_str_eq(result2, "hello");
  free(result2);
  ck_assert_str_eq(result3, "hello");
  free(result3);
  ck_assert_str_eq(result4, "hello123");
  free(result4);
  ck_assert_str_eq(result5, "hello_}(&&*^)");
  free(result5);
}
END_TEST

START_TEST(S21_INSERT) {
  char* result1 = (char*)s21_insert("Hello", "HELLO_WORLD!", 3);
  char* result2 = (char*)s21_insert("HELLO", "340568934OUIJK<L<", 1);
  char* result3 = (char*)s21_insert("HeLlO", "0", 0);
  char* result4 = (char*)s21_insert("hello123", "", 0);
  char* result5 = (char*)s21_insert("Hello_}(&&*^)", "_", 6);
  ck_assert_str_eq(result1, "HelHELLO_WORLD!lo");
  free(result1);
  ck_assert_str_eq(result2, "H340568934OUIJK<L<ELLO");
  free(result2);
  ck_assert_str_eq(result3, "0HeLlO");
  free(result3);
  ck_assert_str_eq(result4, "hello123");
  free(result4);
  ck_assert_str_eq(result5, "Hello__}(&&*^)");
  free(result5);
}
END_TEST

START_TEST(S21_TRIM) {
  char* result1 = (char*)s21_trim("11Hello11", "11");
  char* result2 = (char*)s21_trim("  HELLO  ", "  ");
  char* result3 = (char*)s21_trim("HeLlO0", "0");
  char* result4 = (char*)s21_trim("_hello123__", "__");
  char* result5 = (char*)s21_trim("Hello_}(&&*^)", "_");
  ck_assert_str_eq(result1, "Hello");
  free(result1);
  ck_assert_str_eq(result2, "HELLO");
  free(result2);
  ck_assert_str_eq(result3, "HeLlO");
  free(result3);
  ck_assert_str_eq(result4, "hello123");
  free(result4);
  ck_assert_str_eq(result5, "Hello_}(&&*^)");
  free(result5);
}
END_TEST

Suite* make_s21string_suite() {
  Suite* suite = suite_create("s21_string");
  TCase* group = tcase_create("source");

  tcase_add_test(group, S21_MEMCHR);
  tcase_add_test(group, S21_MEMCMP);
  tcase_add_test(group, S21_MEMCPY);
  tcase_add_test(group, S21_MEMSET);
  tcase_add_test(group, S21_STRNCAT);
  tcase_add_test(group, S21_STRCHR);
  tcase_add_test(group, S21_STRCSPN);
  tcase_add_test(group, S21_STRERROR);
  tcase_add_test(group, S21_STRNCMP);
  tcase_add_test(group, S21_STRNCPY);
  tcase_add_test(group, S21_STRLEN);
  tcase_add_test(group, S21_STRPBRK);
  tcase_add_test(group, S21_STRRCHR);
  tcase_add_test(group, S21_STRSTR);
  tcase_add_test(group, S21_STRTOK);
  tcase_add_test(group, S21_SSCANF);
  tcase_add_test(group, SSCANF_D);
  tcase_add_test(group, SSCANF_LD_HD);
  tcase_add_test(group, SSCANF_U);
  tcase_add_test(group, SSCANF_LU_HU);
  tcase_add_test(group, SSCANF_O);
  tcase_add_test(group, SSCANF_LO_HO);
  tcase_add_test(group, SSCANF_X_P);
  tcase_add_test(group, SSCANF_LX_HX);
  tcase_add_test(group, SSCANF_I);
  tcase_add_test(group, SSCANF_LI_HI);
  tcase_add_test(group, SSCANF_F);
  tcase_add_test(group, SSCANF_LF);
  tcase_add_test(group, SSCANF_C_S);
  tcase_add_test(group, SSCANF_N);
  tcase_add_test(group, SSCANF_PROCENT);
  tcase_add_test(group, S21_SPRINTF);
  tcase_add_test(group, SPRINTF_C);
  tcase_add_test(group, SPRINTF_S);
  tcase_add_test(group, SPRINTF_D);
  tcase_add_test(group, SPRINTF_LD);
  tcase_add_test(group, SPRINTF_U);
  tcase_add_test(group, sprintf_1_u);
  tcase_add_test(group, sprintf_2_u);
  tcase_add_test(group, sprintf_3_u);
  tcase_add_test(group, sprintf_4_u);
  tcase_add_test(group, sprintf_5_u);
  tcase_add_test(group, sprintf_6_u);
  tcase_add_test(group, sprintf_7_u);
  tcase_add_test(group, sprintf_8_u);
  tcase_add_test(group, sprintf_9_u);
  tcase_add_test(group, sprintf_11_u);
  tcase_add_test(group, sprintf_12_u);
  tcase_add_test(group, sprintf_17_u);
  tcase_add_test(group, sprintf_18_u);
  tcase_add_test(group, sprintf_19_u);
  tcase_add_test(group, sprintf_20_u);
  tcase_add_test(group, sprintf_21_u);
  tcase_add_test(group, sprintf_1_lu);
  tcase_add_test(group, sprintf_2_lu);
  tcase_add_test(group, sprintf_3_lu);
  tcase_add_test(group, sprintf_4_lu);
  tcase_add_test(group, sprintf_5_lu);
  tcase_add_test(group, sprintf_6_lu);
  tcase_add_test(group, sprintf_7_lu);
  tcase_add_test(group, sprintf_8_lu);
  tcase_add_test(group, sprintf_9_lu);
  tcase_add_test(group, sprintf_11_lu);
  tcase_add_test(group, sprintf_12_lu);
  tcase_add_test(group, sprintf_17_lu);
  tcase_add_test(group, sprintf_18_lu);
  tcase_add_test(group, sprintf_19_lu);
  tcase_add_test(group, sprintf_20_lu);
  tcase_add_test(group, sprintf_21_lu);
  tcase_add_test(group, SPRINTF_F);
  tcase_add_test(group, S21_TO_UPPER);
  tcase_add_test(group, S21_TO_LOWER);
  tcase_add_test(group, S21_INSERT);
  tcase_add_test(group, S21_TRIM);

  suite_add_tcase(suite, group);
  return suite;
}

int main() {
  SRunner* suite_runner = srunner_create(make_s21string_suite());
  srunner_run_all(suite_runner, CK_NORMAL);
  srunner_free(suite_runner);

  return 0;
}
