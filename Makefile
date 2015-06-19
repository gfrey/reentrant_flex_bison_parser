.PHONY: clean mem

CC := clang
CFLAGS := -g

run: parser.tab.o lex.yy.o ast.o module.o main.o
	$(CC) -g -o $@ $+

mem:
	valgrind --leak-check=full ./run

clean:
	rm -f run *.o lex.yy.c parser.tab* scanner.h

parser.tab.o: lex.yy.c

lex.yy.c: scanner.l
	flex --header-file=scanner.h scanner.l

parser.tab.c: parser.y
	bison -d parser.y
