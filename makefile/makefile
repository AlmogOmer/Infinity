CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g

all : fooer.out main.o foo.o

debug: CFLAGS += -DDEBUG -g
debug: fooer.out

fooer.out : foo.o main.o 
	$(CC) -o fooer.out foo.o main.o

main.o : main.c foo.h 
	$(CC) -c main.c 

foo.o : foo.c foo.h 
	$(CC) -c foo.c 
	
libfoo.ar : foo.o main.o foo.h
	ar -rv libfoo.ar foo.o main.o foo.h

clean :
	rm fooer.out main.o foo.o
