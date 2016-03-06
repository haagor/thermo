# make && time ./main -s 3 -M -m -i 10000

CC = gcc
CCFLAGS = -g -std=c99 -Wall

default: ./bin/main

./bin/main: ./bin/main.o ./bin/utils.o ./bin/matrix.o ./bin/e0/heaTransfert.o ./bin/e1/heaTransfert.o
	@mkdir -p bin
	$(CC) $(CCFLAGS) -o ./bin/main $^ -lpthread

./bin/main.o: ./src/main.c ./src/utils.h ./src/e0/heaTransfert.h ./src/e1/heaTransfert.h
	@mkdir -p bin
	$(CC) $(CCFLAGS) -c ./src/main.c -o $@

./bin/matrix.o: ./src/matrix.c ./src/matrix.h
	@mkdir -p bin
	$(CC) $(CCFLAGS) -c ./src/matrix.c -o $@

./bin/utils.o: ./src/utils.c ./src/utils.h
	@mkdir -p bin
	$(CC) $(CCFLAGS) -c ./src/utils.c -o $@

# E0
./bin/e0/heaTransfert.o: ./src/e0/heaTransfert.c ./src/e0/heaTransfert.h ./src/matrix.h
	@mkdir -p bin/e0
	$(CC) $(CCFLAGS) -c ./src/e0/heaTransfert.c -o $@

# E1
./bin/e1/heaTransfert.o: ./src/e1/heaTransfert.c ./src/e1/heaTransfert.h ./src/matrix.h
	@mkdir -p bin/e1
	$(CC) $(CCFLAGS) -c ./src/e1/heaTransfert.c -o $@

clean:
	$(RM) -rf *.o *~ ./bin
