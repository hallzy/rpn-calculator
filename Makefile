all:
	gcc -Wall -Werror main.c stack.c operations.c -o calc -lm
clean:
	rm -rf calc
