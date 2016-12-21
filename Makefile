.PHONY: clean mem

CC := gcc
CFLAGS := -g $(shell pkg-config --cflags libedit)
LDFLAGS := $(shell pkg-config --libs libedit)

run: my_parser.o my_scanner.o ast.o module.o main.o
	$(CC) -g -o $@ $+ $(LDFLAGS)

mem:
	valgrind --leak-check=full ./run

clean:
	rm -f run *.o my_parser.[ch] my_scanner.[ch]

my_parser.o: my_scanner.c

my_scanner.c: my_scanner.l
	flex -P my_ --header-file=my_scanner.h -o $@ $^

my_parser.c: my_parser.y
	bison -d -p my_ -o $@ $^
