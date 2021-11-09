CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g

output: singly_list.o singly_list_tests.o
	$(CC) -o output singly_list.o singly_list_tests.o

singly_list.o: singly_list.c singly_list.h
	$(CC) -c singly_list.c

singly_list_test.o: singly_list_tests.c singly_list.h
	$(CC) -c singly_list_tests.c

clean:
	rm output singly_list.o singly_list.o

all:    output singly_list.o singly_list.o

debug:    CCFLAGS += -DDEBUG
debug:    executable

libLingList.ar: singly_list.o singly_list_tests.o singly_list.h
	ar -rv libLingList.a singly_list.o singly_list.h
