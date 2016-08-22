ROOT_PATH=$(shell pwd)

INCLUDE_PATH=$(ROOT_PATH)/lib/include
LIB_PATH=$(ROOT_PATH)/lib
COMM_PATH=$(ROOT_PATH)/comm
SERVER_PATH=$(ROOT_PATH)/server


SER=xshell
CC=g++
FIND_INCLUDE=-I$(INCLUDE_PATH) -I$(COMM_PATH) -I$(SERVER_PATH)
FIND_LIB=-L$(LIB_PATH)
LDFLAGS=-ljson -pthread


SER_SRC=$(shell ls $(SERVER_PATH) | grep -E "*.cpp")
SER_SRC+=$(shell ls $(COMM_PATH) | grep -E "*.cpp")
SER_OBJ=$(SER_SRC:.cpp=.o)

$(SER):$(SER_OBJ)
	@$(CC) -o $(@) $(^) $(FIND_LIB) $(LDFLAGS)
	@echo "Linking [ $(^) ] to [ $(@) ] ... done"
%.o:$(SERVER_PATH)/%.cpp
	@$(CC) -c $(<) $(FIND_INCLUDE)
	@echo "Compling [ $(<) ] to [ $(@) ] ... done"
%.o:$(COMM_PATH)/%.cpp
	@$(CC) -c $(<) $(FIND_INCLUDE)
	@echo "Compling [ $(<) ] to [ $(@) ] ... done"



.PHONY:clean
clean:
	@rm -f $(SER) *.o
	@echo "clean ... done"
	

.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $(SER_SRC)
	@echo $(SER_OBJ)
