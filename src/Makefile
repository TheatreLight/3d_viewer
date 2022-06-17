OS=$(shell uname)
BUILD_TESTS_DIR=build-s21_viewer-Desktop_Qt_6_2_4_GCC_64bit-C-Tests
INSTALL_DIR=3Dviewer
OPEN=
DIR=
ifeq ($(OS), Linux)
	QMAKE=qmake
	OPT=-spec linux-g++ CONFIG+=qtquickcompiler
	BUILD_DIR=build-s21_viewer-Desktop_Qt_6_2_4_GCC_64bit-Release
	DIR=
	LIBS=-lcheck -lpthread -lrt -lm -lsubunit
	OPEN=xdg-open
else
	QMAKE=qmake
	OPT=CONFIG+=qtquickcompiler
	BUILD_DIR=build-s21_viewer-Desktop_Qt_6_2_4_GCC_64bit-Release/
	DIR=s21_viewer.app/Contents/MacOS
	LIBS=-lcheck -lm
	OPEN=open
endif

all: build

rebuild: clean all

install:
	@mkdir -p $(INSTALL_DIR)
	@cp -r $(BUILD_DIR)$(DIR)/s21_viewer $(INSTALL_DIR)/s21_viewer
	@cp -r objs $(INSTALL_DIR)/examples
	@cp -r $(BUILD_DIR)$(DIR)/Settings.conf $(INSTALL_DIR)
	@make dvi
	@cp man.pdf $(INSTALL_DIR)/man.pdf

uninstall:
	@rm -rf $(INSTALL_DIR)

dist: clean
	tar -czf "ghumbleb_3dviewer.tgz" objs models test *.c *.h *.cpp *.ui *.tex *.pro *.conf Makefile 

dvi:
	texi2dvi -p man.tex

tests:
	make -C models build
	cp -r test/resurces $(BUILD_TESTS_DIR)/resurces
	cp -r test/makefile $(BUILD_TESTS_DIR)/
	$(CC) test/c_tests.c -L./$(BUILD_TESTS_DIR) -lobjparser -o $(BUILD_TESTS_DIR)/c_tests.out $(LIBS)
	make run_test

gcov_report:
	make -C models build_dir
	cp -r test/makefile $(BUILD_TESTS_DIR)/
	cp -r test/resurces $(BUILD_TESTS_DIR)/resurces
	make -C models gcov_report
	lcov -t "$(BUILD_TESTS_DIR)с_tests" -o test.info -c -d .
	genhtml -o report test.info
	$(OPEN) report/index.html

build:
	$(QMAKE) -o $(BUILD_DIR)/Makefile s21_viewer.pro $(OPT)
	make -C $(BUILD_DIR)/ first
	cp Settings.conf $(BUILD_DIR)$(DIR)

run_test:
	make -C $(BUILD_TESTS_DIR) run

run:
	./$(BUILD_DIR)$(DIR)/s21_viewer

check:
	cppcheck --enable=all --suppress=missingInclude --suppress=unusedFunction --suppress=knownConditionTrueFalse s21_conf.c s21_conf.h test/*.c models/*.c models/*.h
	cppcheck --enable=all --suppress=missingInclude --suppress=unusedFunction *.cpp mainwindow.h gl_view.h --std=c++11 --language=c++
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h test/*.c models/*.c models/*.h

clean:
	rm -rf *.tgz *.o *.a *.out *.gcda *.gcno *.info *.pdf *.dvi *.log *.aux *.dSYM *.info report build*

leaks:  clean tests
	make -C $(BUILD_TESTS_DIR) leaks
