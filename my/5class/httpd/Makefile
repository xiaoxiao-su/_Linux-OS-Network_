PWD=$(shell pwd)
BIN=httpd
SRC=httpd.c
INCLUDE=.
CC=gcc
FLAGS=-o
LDFLAGS=#-static
LIB=

$(BIN):$(SRC) 
	$(CC) $(FLAGS) $@ $^ $(LDFLAGS)
.PHONY:clean
clean:
	rm -rf $(BIN)
