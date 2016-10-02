ROOT_PATH=$(shell pwd)
INCLUDE=$(ROOT_PATH)/lib/include
LIB=$(ROOT_PATH)/lib/lib

.PHONY:all
all: select_cgi insert_cgi

select_cgi:sql_api.cpp select_cgi.cpp
	g++ -o $@ $^ -L$(LIB) -I$(INCLUDE) -lmysqlclient
insert_cgi:sql_api.cpp insert_cgi.cpp
	g++ -o $@ $^ -L$(LIB) -I$(INCLUDE) -lmysqlclient

.PHONY:clean
clean:
	rm -f select_cgi insert_cgi
