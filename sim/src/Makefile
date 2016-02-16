
CC = gcc
CCFLAGS = -g -std=c11 -Wall

default: main

main:  main.o matrix.o heaTransfert.o fct.o
	$(CC) $(CCFLAGS) -o main main.o matrix.o heaTransfert.o fct.o

main.o:  main.c matrix.h heaTransfert.h
	$(CC) $(CCFLAGS) -c main.c

matrix.o:  matrix.c matrix.h
	$(CC) $(CCFLAGS) -c matrix.c

heaTransfert.o:  heaTransfert.c heaTransfert.h matrix.h 
	$(CC) $(CCFLAGS) -c heaTransfert.c

fct.o:  fct.c 
	$(CC) $(CCFLAGS) -c fct.c

clean: 
	$(RM) count *.o *~