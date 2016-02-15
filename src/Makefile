<<<<<<< Updated upstream
INITIAL_FILES = thermique.cpp
=======
INITIAL_FILES = thermique.c
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	-rm -f *.o $(ALL)
=======
	-rm -f *.o $(ALL)
>>>>>>> Stashed changes