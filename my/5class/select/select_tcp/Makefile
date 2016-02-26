#my_select:my_select.c
#	gcc -o $@ $^
#.PHONY:clean
#clean:
#	rm -rf my_select


.PHONY:all
all:select_server select_client

select_server:select_server.c
	gcc -o $@ $^
select_client:select_client.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -rf select_server select_client

