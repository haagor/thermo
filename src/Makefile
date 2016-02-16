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
<<<<<<< e1a1ac05c344a6a883dad375dcba732c352a2754
	-rm -f *.o $(ALL)
=======
	-rm -f *.o $(ALL)

>>>>>>> 5fa869e2e498c5c13ab0ab8f8c498d234fa5383e
