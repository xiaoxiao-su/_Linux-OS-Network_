ROOT_PWD=$(shell pwd)
SRC=$(shell ls -R | grep -E '*.cpp')
OBJ=$(SRC:.cpp=.o)

DATA=$(ROOT_PWD)/database
SOCK=$(ROOT_PWD)/sock
MEMC=$(ROOT_PWD)/memc
SERVER=$(ROOT_PWD)/server

CC=g++
FLAGS=-std=c++0x 
LIB_PATH= -L /usr/local/lib -L /usr/lib/mysql
LINK_LIB=-lboost_thread -lpthread  -lmemcached -lmysqlclient
INCLUDE= -I /usr/local/include -I$(DATA) -I$(SOCK) -I$(MEMC) 

httpd: $(OBJ)
	$(CC) -o $@ $^ $(LINK_LIB) $(LIB_PATH)  

%.o:$(SERVER)/%.cpp
	$(CC) -c $< $(INCLUDE) $(FLAGS)
%.o:$(DATA)/%.cpp
	$(CC) -c $< 
%.o:$(SOCK)/%.cpp
	$(CC) -c $<
%.o:$(MEMC)/%.cpp
	$(CC) -c $< $(FLAGS)

.PHONY:clean
clean:
	rm httpd *.o
