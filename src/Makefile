SOURCES := $(wildcard *.c)
gcov:
	gcc -fprofile-arcs -ftest-coverage -Wall -Werror -DTEST -I../include -I../tests ../tests/test.c $(SOURCES) -o calc-test -lm
	./calc-test
run-gcov:
	gcov -bfc *.c
lcov:
	gcc -coverage -Wall -Werror -DTEST -I../include -I../tests ../tests/test.c $(SOURCES) -o calc-test -lm
	./calc-test
	lcov --capture --directory ./ --output-file coverage.info
	genhtml coverage.info --output-directory out
	firefox out/index.html
clean:
	rm -rf calc calc-test *.gcno *.gcda out coverage.info
