SOURCES := $(wildcard src/*.c)
all:
	gcc -Wall -Werror -Iinclude $(SOURCES) -o calc -lm
	gcc -Wall -Werror -DTEST -Iinclude -Itests tests/test.c $(SOURCES) -o test -lm
clean:
	rm -rf calc test
