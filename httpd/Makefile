ROOT_PATH=$(shell pwd)
SER_PATH=$(ROOT_PATH)/server
CC=gcc
LDFLAGS=-lpthread
SER=httpd
SER_SRC=$(shell ls $(SER_PATH) | grep -E '*.c')
SER_OBJ=$(SER_SRC:.c=.o)
CGI_PATH=cgi sql_cgi

.PHONY:all
all:$(SER) cgi

$(SER):$(SER_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
%.o:$(SER_PATH)/%.c
	$(CC) -c $<

.PHONY:cgi
cgi:
	for i in `echo $(CGI_PATH)`;\
	do\
		cd $$i;\
		make;\
		cd -;\
	done

.PHONY:output
output:all
	mkdir -p output/htdocs
	cp $(SER) output
	cp cgi/math_cgi output/htdocs
	cp sql_cgi/select_cgi output/htdocs
	cp sql_cgi/insert_cgi output/htdocs
	cp htdocs/index.html output/htdocs
	cp htdocs/select.html output/htdocs
	cp -rf htdocs/image output/htdocs

.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $(SER_PATH)
	@echo $(SER_SRC)
	@echo $(SER_OBJ)

.PHONY:clean
clean:
	rm -rf *.o $(SER) output
	for i in `echo $(CGI_PATH)`;\
	do\
		cd $$i;\
		make clean;\
		cd -;\
	done
