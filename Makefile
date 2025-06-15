CC = gcc
DEBUG ?= 0
CFLAGS = -Iinclude -Wall $(if $(DEBUG),-DDEBUG_PARSER)

SRC = src/main.c src/interpreter.c src/semantic.c src/lexer.c src/error.c src/parser.c src/codegen.c src/ast.c

all:
	$(CC) $(CFLAGS) $(SRC) -o minic

clean:
	rm -f minic *.o