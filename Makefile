all:
	gcc -Wall -Werror main.c stack.c operations.c -o calc -lm
	gcc -Wall -Werror -DTEST main.c stack.c operations.c test.c -o test -lm
clean:
	rm -rf calc test
