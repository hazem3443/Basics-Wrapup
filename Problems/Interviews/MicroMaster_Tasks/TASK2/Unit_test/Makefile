CC = g++

CFLAGS = -g -w -Wall

main: main.o util.o
	$(CC) $(CLAGS) -o main main.o util.o

test_unit: test_unit.o util.o
	$(CC) $(CLAGS) -o test_unit test_unit.o util.o

util.o:util.hpp util.cpp
	$(CC) $(CLAGS) -c util.cpp

clean:
	rm -f core *.o main test_unit