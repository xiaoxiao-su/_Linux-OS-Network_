SER=server
CLI=client
CC=gcc

.PHONY:all
all:$(CLI) $(SER)

$(CLI):client.c msgqueue.c
	$(CC) -w -o $@ $^
$(SER):server.c msgqueue.c
	$(CC) -w -o $@ $^

.PHONY:clean
clean:
	rm -rf $(CLI) $(SER)

