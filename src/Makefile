<<<<<<< HEAD
CC = gcc

OBJ_FICHIER = main.c

EXE = main

OPTION = -std=c11

all: $(EXE)
	
#Exécutable
main:
	$(CC) $(OPTION) $(OBJ_FICHIER) -lm -o $(EXE)

clean: 
	rm -vf main
=======




INITIAL_FILES = thermique.cpp
ALL = thermique
CXX_FLAGS= -Wall -std=c11 
CXX_LINK=gcc

# targets
thermique : thermique.o
		$(CXX_LINK) -o thermique thermique.o
#
#dox : $(wildcard *.h *.cpp)
#	doxygen 
#	date > dox
#

thermique.o : thermique.h 
	$(CXX_LINK) -o thermique.o -c thermique.c $(CXX_FLAGS)

clear : 
	-rm -f *.o
clean :
	-rm -f *.o $(ALL)
>>>>>>> 989798ee63db8e85f870db82a34febf34543867e
