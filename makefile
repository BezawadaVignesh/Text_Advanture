# Makefile

# the C++ compiler
CXX     = g++
#CXXVERSION = $(shell g++ --version | grep ^g++ | sed 's/^.* //g')

# options to pass to the compiler
CXXFLAGS = -O0 -g3 -std=c++14

All: all
all: main 

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

deepclean:
	rm -f *~ *.o main *.exe *.stackdump

clean:
	rm -f *~ *.o *.stackdump

