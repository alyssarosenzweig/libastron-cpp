CXX=clang++
FLAGS=-std=c++0x -I.
LIBS=-lbamboo

all: ConnectionRepository.o test_air.o
	$(CXX) test_air.o ConnectionRepository.o $(FLAGS) $(LIBS) -o test_air

ConnectionRepository.o: ConnectionRepository.cpp
	$(CXX) -c ConnectionRepository.cpp $(FLAGS)

test_air.o: test_air.cpp
	$(CXX) -c test_air.cpp $(FLAGS)