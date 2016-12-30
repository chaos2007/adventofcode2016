SOURCES = IPv7Decoder.cpp Test_IPv7Decoder.cpp
FLAGS = -std=c++11 -g
GCC = g++

all: test

test: compile
	./a.out

compile:
	$(GCC) $(SOURCES) -lgtest -lgtest_main $(FLAGS)

