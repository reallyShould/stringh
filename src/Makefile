CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
ADDFLAGS = -lcheck -lsubunit -lm -lrt -pthread

HEADER = s21_string.h
SOURCES = $(wildcard ./source/*.c) $(wildcard ./IO/*.c)
TESTS = $(wildcard ./tests/*.c)

OBJ_LIBRARY := $(patsubst %.c, %.o, $(SOURCES))

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: s21_string.a

s:
	echo $(OBJ_LIBRARY)

s21_string.a: $(OBJ_LIBRARY) $(HEADER)
	ar rcs s21_string.a $(OBJ_LIBRARY)
	ranlib s21_string.a
	rm -rf ./*/*.o

clang_sources:
	clang-format -i --style=Google $(SOURCES)

clang_header:
	clang-format -i --style=Google $(HEADER)

clang_test:
	clang-format -i --style=Google $(TESTS)

clang: clang_sources clang_header clang_test

clang_check:
	clang-format -n --style=Google $(SOURCES)
	clang-format -n --style=Google $(HEADER)
	clang-format -n --style=Google $(TESTS)

clean:
	rm -rf ./*/*.o
	rm -rf s21_string.a
	rm -rf *.out
	rm -rf ./tests/*.gcda
	rm -rf ./tests/*.gcno
	rm -rf ./tests/report
	rm -rf ./tests/*.out
	rm -rf ./tests/*.info
	rm -rf *.gcov
	rm -rf *.gcno

test: s21_string.a tests/s21_test.c
	gcc $(CFLAGS) tests/s21_test.c s21_string.a -o test.out $(ADDFLAGS)
	./test.out

valgrind_test: s21_string.a tests/s21_test.c
	gcc $(CFLAGS) tests/s21_test.c s21_string.a -o test.out $(ADDFLAGS)
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./test.out

gcov_report: tests/s21_test.c s21_string.a
	gcc $(GCOVFLAGS) tests/s21_test.c $(SOURCES) -o ./tests/report.out $(ADDFLAGS)
	./tests/report.out
	gcov -f ./tests/report.out-*
	lcov -t "gcov_report" -o tests/Coverage_Report.info -c -d .
	genhtml -o tests/report tests/Coverage_Report.info
	rm -f *.gcno *.gcda tests/*.info tests/report.out *.gcov
