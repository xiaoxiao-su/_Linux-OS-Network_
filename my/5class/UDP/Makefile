CLI=udp_client
SER=udp_server
CC=gcc
FLAGS=#-static
.PHONY:all
all:$(CLI) $(SER)

$(CLI):udp_client.c
	$(CC) -o $@ $^ $(FLAGS)
$(SER):udp_server.c
	$(CC) -o $@ $^ $(FLAGS)
.PHONY:clean
clean:
	rm -rf $(CLI) $(SER)
