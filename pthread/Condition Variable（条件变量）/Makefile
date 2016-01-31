BIN=cond_mutex
SRC=cond_mutex.c
CC=gcc
FLAGS=-lpthread

$(BIN):$(SRC)
	$(CC) -o $@ $^ $(FLAGS)
.PHONY:clean
clean:
	rm -rf $(BIN)
