ROOT_PATH=$(shell pwd)
SERVER_PATH=$(ROOT_PATH)/server
CLIENT_PATH=$(ROOT_PATH)/client
COMM_PATH=$(ROOT_PATH)/comm
DATA_POOL_PATH=$(ROOT_PATH)/data_pool
LIB_PATH=$(ROOT_PATH)/lib
WINDOW_PATH=$(ROOT_PATH)/window

SER=udp_server
CLI=udp_client
CC=g++
FIND_INCLUDE=-I$(COMM_PATH) -I$(DATA_POOL_PATH) -I$(LIB_PATH)/include -I$(WINDOW_PATH)
FIND_LIB=-L$(LIB_PATH)
LDFLAGS=-lpthread -ljson

FLAGS=-D_FAST_

SER_SRC=$(shell ls $(SERVER_PATH) | grep -E "*.cpp")
SER_SRC+=$(shell ls $(COMM_PATH) | grep -E "*.cpp")
SER_SRC+=$(shell ls $(DATA_POOL_PATH) | grep -E "*.cpp")
SER_OBJ=$(SER_SRC:.cpp=.o)

CLI_SRC=$(shell ls $(CLIENT_PATH) | grep -E "*.cpp")
CLI_SRC+=$(shell ls $(COMM_PATH) | grep -E "*.cpp")
CLI_SRC+=$(shell ls $(WINDOW_PATH) | grep -E "*.cpp")
CLI_OBJ=$(CLI_SRC:.cpp=.o)

.PHONY:all
all:$(SER) $(CLI)

$(SER):$(SER_OBJ)
	@$(CC) -o $@ $^ $(FIND_LIB) $(LDFLAGS)
	@echo "Linking [ $^ ] to [ $@ ] ... done"
$(CLI):$(CLI_OBJ)
	@$(CC) -o $@ $^ $(FIND_LIB) $(LDFLAGS) -lncurses
	@echo "Linking [ $^ ] to [ $@ ] ... done"
%.o:$(SERVER_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE)
	@echo "Compling [ $< ] to [ $@ ] ... done"
%.o:$(DATA_POOL_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE)
	@echo "Compling [ $< ] to [ $@ ] ... done"
%.o:$(CLIENT_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE)
	@echo "Compling [ $< ] to [ $@ ] ... done"
%.o:$(COMM_PATH)/%.cpp 
	@$(CC) -c $< $(FIND_INCLUDE) $(FLAGS)
	@echo "Compling [ $< ] to [ $@ ] ... done"
%.o:$(WINDOW_PATH)/%.cpp
	@$(CC) -c $< $(FIND_INCLUDE) -ljson
	@echo "Compling [ $< ] to [ $@ ] ... done"

.PHONY:clean
clean:
	@rm -f $(SER) $(CLI) *.o
	@echo "clean ... done"

.PHONY:output
output: $(SER) $(CLI)
	@mkdir -p output/server
	@mkdir -p output/client
	@cp -rf log output/server
	@cp -rf conf output/client
	@cp -rf conf output/server
	@cp -f $(CLI) output/client
	@cp -f $(SER) output/server
	@cp plugin/ctl_server.sh output/server
	@cp plugin/ctl_client.sh output/client

	
.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $(SER_SRC)
	@echo $(SER_OBJ)
	@echo $(CLI_SRC)
	@echo $(CLI_OBJ)
