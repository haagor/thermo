
CC = gcc
CCFLAGS = -g -std=c11 -Wall

default: main

main:  main.o matrix.o heaTransfert.o 
	$(CC) $(CCFLAGS) -o main main.o matrix.o heaTransfert.o

main.o:  main.c matrix.h heaTransfert.h
	$(CC) $(CCFLAGS) -c main.c

matrix.o:  matrix.c matrix.h
	$(CC) $(CCFLAGS) -c matrix.c

heaTransfert.o:  heaTransfert.c heaTransfert.h matrix.h 
	$(CC) $(CCFLAGS) -c heaTransfert.c

clean: 
	$(RM) count *.o *~