# make && time ./main -s 3 -M -m -i 10000

CC = gcc
CCFLAGS = -g -std=c11 -Wall

default: ./bin/main

./bin/main:  ./bin/main.o ./bin/matrix.o ./bin/heaTransfert.o ./bin/fct.o
	@mkdir -p bin
	$(CC) $(CCFLAGS) -o ./bin/main ./bin/main.o ./bin/matrix.o ./bin/heaTransfert.o ./bin/fct.o

./bin/main.o:  ./src/main.c ./src/matrix.h ./src/heaTransfert.h
	@mkdir -p bin
	$(CC) $(CCFLAGS) -c ./src/main.c -o $@

./bin/matrix.o:  ./src/matrix.c ./src/matrix.h
	@mkdir -p bin
	$(CC) $(CCFLAGS) -c ./src/matrix.c -o $@

./bin/heaTransfert.o:  ./src/heaTransfert.c ./src/heaTransfert.h ./src/matrix.h 
	@mkdir -p bin
	$(CC) $(CCFLAGS) -c ./src/heaTransfert.c -o $@

./bin/fct.o:  ./src/fct.c 
	@mkdir -p bin
	$(CC) $(CCFLAGS) -c ./src/fct.c -o $@

clean: 
	$(RM) -rf *.o *~ ./bin
