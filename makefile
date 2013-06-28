.PHONY: all clean

all: OCLHelperFunctions.o test

CFLAGS=-Wall

OCLHelperFunctions.o: OCLHelperFunctions.c OCLHelperFunctions.h
	gcc -c OCLHelperFunctions.c

test: test.c OCLHelperFunctions.o
	gcc -o test test.c OCLHelperFunctions.o -lcl

clean:
	rm -f OCLHelperFunctions.o
