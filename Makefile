CC=gcc
CFLAGS=-Iinclude -Wall

SRC=src/main.c src/lexer.c src/parser.c src/codegen.c src/ast.c

all:
	$(CC) $(SRC) -o minic $(CFLAGS)

clean:
	rm -f minic *.o
