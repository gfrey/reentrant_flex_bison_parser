.PHONY: clean

CC := clang

run: parser.tab.o lex.yy.o main.o
	$(CC) -o $@ $+

clean:
	rm -f run *.o lex.yy.c parser.tab* scanner.h

parser.tab.o: lex.yy.c

lex.yy.c: scanner.l
	flex --header-file=scanner.h scanner.l

parser.tab.c: parser.y
	bison -d parser.y
