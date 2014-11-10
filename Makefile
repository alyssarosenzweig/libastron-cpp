CXX=clang++
FLAGS=-std=c++0x -I. -g
LIBS=-lbamboo -lboost_system

all: ConnectionRepository.o Connection.o AIRepository.o test_air.o
	$(CXX) test_air.o ConnectionRepository.o AIRepository.o Connection.o $(FLAGS) $(LIBS) -o test_air

ConnectionRepository.o: ConnectionRepository.cpp
	$(CXX) -c ConnectionRepository.cpp $(FLAGS)

AIRepository.o: AIRepository.cpp
	$(CXX) -c AIRepository.cpp $(FLAGS)

Connection.o: Connection.cpp
	$(CXX) -c Connection.cpp $(FLAGS)

test_air.o: test_air.cpp
	$(CXX) -c test_air.cpp $(FLAGS)

clean:
	rm *.o