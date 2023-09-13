FILES = SmartCalc/*.c 
TEST = test.c 
CC = gcc -std=c11
FLAGS = -Wall -Wextra -Werror

all: clean install dvi dist test gcov_report

install:
	make clean
	mkdir build
	cd SmartCalc && qmake && make && make clean && rm Makefile && rm .qmake.stash
	mv SmartCalc/SmartCalc.app build
	cd build && open SmartCalc.app

uninstall:
	-rm -rf build tgz_SmartCalc.tgz

clean:
	-rm -rf *.o *.a test *.gcno *.gcda gcov_test test.info report *.out build
	cd SmartCalc && qmake && make clean && rm Makefile && rm .qmake.stash && rm -rf *.user
	rm -rf build tgz_SmartCalc.tgz

dvi:
	open readme.md

dist:
	tar cvzf tgz_SmartCalc.tgz build/SmartCalc.app
	rm -rf tgz_SmartCalc/

test: 
	$(CC) $(FLAGS) -c $(FILES)
	$(CC) $(FLAGS) $(TEST) -o test *.o -pthread -lcheck -pthread -lm

	rm *.o
	./test

gcov_report:
	$(CC) $(FLAGS) -fprofile-arcs -ftest-coverage $(TEST) $(FILES) -pthread -lcheck -pthread -lm -o gcov_test
	./gcov_test
	lcov -t "report" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
