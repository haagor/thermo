INITIAL_FILES = thermique.c
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

