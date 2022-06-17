CC=gcc
CFLAGS=-Werror -Wall -Wextra -std=c11
CTESTCORE=../test/c_tests.c
CORE=data.c polygons.c s21_matrix.c string_util.c objparser.c affinity.c
BUILD_TESTS_DIR=../build-s21_viewer-Desktop_Qt_6_2_4_GCC_64bit-C-Tests/
CTEST=$(BUILD_TESTS_DIR)c_tests.out

OS=$(shell uname)
ifeq ($(OS), Linux)
	LIBS=-lcheck -lpthread -lrt -lm -lsubunit
	OPEN=xdg-open
	LEAKS=CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes

else
    LIBS=-lcheck -lm
	OPEN=open
	LEAKS=CK_FORK=no leaks --atExit --
endif

all: clean build

build_dir:
	mkdir -p $(BUILD_TESTS_DIR)

polygons.o:
	$(CC) -c polygons.c -o $(BUILD_TESTS_DIR)polygons.o

s21_matrix.o:
	$(CC) -c s21_matrix.c -o $(BUILD_TESTS_DIR)s21_matrix.o

data.o: polygons.o s21_matrix.o
	$(CC) -c data.c -o $(BUILD_TESTS_DIR)data.o

string_util.o:
	$(CC) -c string_util.c -o $(BUILD_TESTS_DIR)string_util.o

affinity.o:
	$(CC) -c affinity.c -o $(BUILD_TESTS_DIR)affinity.o

objparser.a: data.o string_util.o affinity.o
	$(CC) -c objparser.c -o $(BUILD_TESTS_DIR)objparser.o
	ar rcs $(BUILD_TESTS_DIR)libobjparser.a $(BUILD_TESTS_DIR)objparser.o $(BUILD_TESTS_DIR)data.o $(BUILD_TESTS_DIR)string_util.o $(BUILD_TESTS_DIR)polygons.o $(BUILD_TESTS_DIR)s21_matrix.o $(BUILD_TESTS_DIR)affinity.o
	ranlib $(BUILD_TESTS_DIR)libobjparser.a

# Todo: дополнить
build: build_dir objparser.a

# Todo: сделать в цели сборки qt
uninstall:
	# rm -rf ../mycalc

clean:
	rm -rf *.tgz *.o *.a *.out *.gcda *.gcno *.info *.dvi *.log *.aux *.dSYM *.info

distr: clean
	tar -czf "ghumbleb_3dviewer.tgz" models test *.h *.cpp *.ui *.tex *.pro makefile 

gcov_report:
	$(CC) -o $(CTEST) --coverage $(CTESTCORE) $(CORE) $(LIBS)
	make run

run:
	make -C $(BUILD_TESTS_DIR) run

leaks:
	make -C $(BUILD_DIR) leaks
