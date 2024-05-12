CFLAGS := -Wall -Wextra -Werror -std=c++17
OS := $(shell uname -s)
LIB_SOURCE_FILES := s21_matrix_oop.cc
TESTS_SOURCE_FILES := test.cc
CC := g++
LIB = s21_matrix_oop.a
# Определение операционной системы
ifeq ($(OS), Darwin)
	TEST_FLAGS = -lgtest -lpthread
else
	TEST_FLAGS = -pthread -lrt -lm -lsubunit
endif

all: clean s21_matrix_oop.a test

clean:
	rm -rf test *.o *.a

test: clean
	${CC} ${CFLAGS} ${LIB_SOURCE_FILES} ${TESTS_SOURCE_FILES} -o test ${TEST_FLAGS}
	./test

s21_matrix_oop.a:
	${CC} ${CFLAGS} -D_GNU_SOURCE -g -c ${LIB_SOURCE_FILES}
	ar rc s21_matrix_oop.a s21_*.o
	rm -rf *.o
	ranlib s21_matrix_oop.a

.PHONY : all clean test s21_matrix_oop.a
