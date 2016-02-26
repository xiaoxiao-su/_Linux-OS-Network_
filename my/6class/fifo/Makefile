SER=server
CLI=client

.PHONY:all
all:$(SER) $(CLI) 

$(SER):server.c
	gcc -o $@ $^
$(CLI):client.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -rf $(SER) $(CLI)
