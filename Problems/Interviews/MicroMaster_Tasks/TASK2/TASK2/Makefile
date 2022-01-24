CC = g++

CFLAGS = -g -w -Wall

main: Task2.o Result.o Topology.o Component.o 
	$(CC) $(CLAGS) -o main Task2.o Result.o Topology.o Component.o -ljsoncpp

unit_tests: unit_tests.o Result.o Topology.o Component.o
	$(CC) $(CLAGS) -o unit_tests unit_tests.o Result.o Topology.o Component.o -ljsoncpp

Result.o:Result.h Result.cpp
	$(CC) $(CLAGS) -c Result.cpp

Topology.o:Topology.h Topology.cpp
	$(CC) $(CLAGS) -c Topology.cpp

Component.o:Component.h Component.cpp
	$(CC) $(CLAGS) -c Component.cpp

clean:
	rm -f core *.o main unit_tests