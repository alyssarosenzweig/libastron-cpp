FLAGS=-std=c++0x -I.
LIBS=-lbamboo

all: ConnectionRepository.o test_air.o
	clang++ test_air.o ConnectionRepository.o $(FLAGS) $(LIBS) -o test_air

ConnectionRepository.o: ConnectionRepository.cpp
	clang++ -c ConnectionRepository.cpp $(FLAGS)

test_air.o: test_air.cpp
	clang++ -c test_air.cpp $(FLAGS)