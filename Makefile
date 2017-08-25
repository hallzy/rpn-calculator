SOURCES := $(wildcard src/*.c)
all:
	gcc -Wall -Werror -Iinclude $(SOURCES) -o calc -lm
	gcc -Wall -Werror -DTEST -Iinclude -Itests tests/test.c $(SOURCES) -o calc-test -lm
test:
	# Compiling tests
	gcc -Wall -Werror -DTEST -Iinclude -Itests tests/test.c $(SOURCES) -o calc-test -lm
	# Running Tests with Valgrind
	valgrind --leak-check=full --show-reachable=yes ./calc-test
clean:
	rm -rf calc calc-test
