CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra

all: main

main: main.o SingleLinkedList.o
    $(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp SingleLinkedList.h
    $(CXX) $(CXXFLAGS) -c $<

SingleLinkedList.o: SingleLinkedList.cpp SingleLinkedList.h
    $(CXX) $(CXXFLAGS) -c $<

clean:
    rm -f main main.o SingleLinkedList.o
