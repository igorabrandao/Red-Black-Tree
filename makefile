#
# Makefile build 'Binary Tree project' using Make
#

SOURCES = $(wildcard src/*.cpp)

CC      = g++
CFLAGS  = -c -g -Wall -std=c++11

INC_DIR = ./include
BIN_DIR = ./bin
APP     = $(BIN_DIR)/red_black_tree
LIB_DIR = 
LIBS = 

OBJECTS = $(SOURCES:.cpp=.o)

all: $(SOURCES) $(APP)
    
$(APP): $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LIBS)

.cpp.o:
	$(CC) $< -o $@ $(CFLAGS) -I$(INC_DIR)

.PHONY: clean
clean:
	rm $(OBJECTS) $(APP)

exe:
	$(APP)

val:
	valgrind $(APP)