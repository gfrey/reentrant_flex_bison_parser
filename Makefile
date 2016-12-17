.PHONY: clean mem

CC := clang
CFLAGS := -g $(shell pkg-config --cflags libedit)
LDFLAGS := $(shell pkg-config --libs libedit)

run: parser.tab.o scanner.o ast.o module.o main.o
	$(CC) -g -o $@ $+ $(LDFLAGS)

mem:
	valgrind --leak-check=full ./run

clean:
	rm -f run *.o parser.tab* scanner.[ch]

parser.tab.o: scanner.c

scanner.c: scanner.l
	flex --header-file=scanner.h --outfile=scanner.c scanner.l

parser.tab.c: parser.y
	bison -d parser.y
