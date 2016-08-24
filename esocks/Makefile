ROOT_PATH=$(shell pwd)

COMM_PATH=$(ROOT_PATH)/comm
SERVER_PATH=$(ROOT_PATH)/server
CLIENT_PATH=$(ROOT_PATH)/client

SER=ser
CLI=cli
CC=g++
FLAGS=-pthread
FIND_INCLUDE=-I$(SERVER_PATH) -I$(CLIENT_PATH) -I$(COMM_PATH)

SER_SRC=$(shell ls $(SERVER_PATH) | grep -E ".cpp")
SER_SRC+=$(shell ls $(COMM_PATH) | grep -E ".cpp")
SER_OBJ=$(SER_SRC:.cpp=.o)

CLI_SRC=$(shell ls $(CLIENT_PATH) | grep -E ".cpp")
CLI_SRC+=$(shell ls $(COMM_PATH) | grep -E ".cpp")
CLI_OBJ=$(CLI_SRC:.cpp=.o)


.PHONY:all
all:$(SER) $(CLI)
	@echo "all ... done"
$(SER):$(SER_OBJ)
	@$(CC) -o $(@) $(^) $(FLAGS)
	@echo "Linking [ $(<) ] to [ $(@) ] ... done"
$(CLI):$(CLI_OBJ)
	@$(CC) -o $(@) $(^) $(FLAGS)
	@echo "Linking [ $(<) ] to [ $(@) ] ... done"
%.o:$(SERVER_PATH)/%.cpp
	@$(CC) -c $(<) $(FIND_INCLUDE)
	@echo "Compling [ $(<) ] to [ $(@) ] ... done"
%.o:$(CLIENT_PATH)/%.cpp
	@$(CC) -c $(<) $(FIND_INCLUDE)
	@echo "Compling [ $(<) ] to [ $(@) ] ... done"
%.o:$(COMM_PATH)/%.cpp
	@$(CC) -c $(<) $(FIND_INCLUDE)
	@echo "Compling [ $(<) ] to [ $(@) ] ... done"

.PHONY:clean
clean:
	@rm -rf $(SER) $(CLI) *.o

.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $(SER_SRC)
	@echo $(SER_OBJ)
