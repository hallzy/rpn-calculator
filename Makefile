SOURCES := $(wildcard src/*.c)
all:
	gcc -Wall -Werror -Iinclude $(SOURCES) -o calc -lm
	gcc -Wall -Werror -DTEST -Iinclude -Itests tests/test.c $(SOURCES) -o calc-test -lm
debug:
	gcc -Wall -Werror -DNO_CLEAR -Iinclude $(SOURCES) -o calc -lm
test:
	# Compiling tests
	gcc -Wall -Werror -DTEST -Iinclude -Itests tests/test.c $(SOURCES) -o calc-test -lm
	# Running Tests with Valgrind
	valgrind --leak-check=full --show-reachable=yes ./calc-test
windows:
	/opt/mingw32/bin/i686-w64-mingw32-gcc -std=gnu11 -Wall -Werror -DWINDOWS -D__USE_MINGW_ANSI_STDIO -Iinclude $(SOURCES) -o win32-calc.exe -lm
	/opt/mingw64/bin/x86_64-w64-mingw32-gcc -std=gnu11 -Wall -Werror -DWINDOWS -D__USE_MINGW_ANSI_STDIO -Iinclude $(SOURCES) -o win64-calc.exe -lm
clean:
	rm -rf calc calc-test
