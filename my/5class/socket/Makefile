.PHONY:all
all:server client
server:server.c
	gcc -o $@ $^ 
client:client.c
	gcc -o $@ $^ -lpthread
.PHONY:clean
clean:
	rm -rf client server
