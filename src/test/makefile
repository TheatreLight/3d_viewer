CTEST=c_tests.out

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

run:
	./c_tests.out

leaks: 
	$(LEAKS) ./$(CTEST)
