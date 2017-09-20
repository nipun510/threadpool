
BUILD_DIR = $(abspath .)
PROJECT_DIR = $(BUILD_DIR)/../

THREADPOOL_INC = -I$(PROJECT_DIR)/include
COMPILER = g++
FLAGS = -std=c++11 -Wall -pthread

BOOST_LIB = 
BOOST_INC =

CPP_LIB = 

LIB = $(CPP_LIB) $(BOOST_LIB)
INCLUDES = $(THREADPOOL_INC)

all : clean build

.PHONY: all clean build

%.o : %.cpp
	$(COMPILER) $(FLAGS) $(INCLUDES) $<  -c -o $@


clean:
	rm -rf run

build:main.o
	$(COMPILER) $(FLAGS) $< $(LIB) -o run.lab
	
