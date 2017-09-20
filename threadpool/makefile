
COMPILER = g++

BOOST_LIB = 
BOOST_INC =

CPP_LIB = -pthread

FLAGS = -g -std=c++11 -Wall

all : clean build

clean:
	rm -rf run.lab

build:
	$(COMPILER) $(FLAGS) $(BOOST_INC) main.cpp -c main.o
	$(COMPILER) $(FLAGS)  main.o $(BOOST_LIB)  $(CPP_LIB) -o run.lab
