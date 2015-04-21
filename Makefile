CXX=clang++
FLAGS=-std=c++0x -I. -g
LIBS=-lbamboo -lboost_system -lpthread

OBJECTS= ConnectionRepository.o AIRepository.o Connection.o ChannelWatcher.o DistributedObject.o AIWatcher.o ClientRepository.o DValue.o

all: test_air.o test_client.o $(OBJECTS)
	$(CXX) test_air.o $(OBJECTS) $(FLAGS) $(LIBS) -o test_air
	$(CXX) test_client.o $(OBJECTS) $(FLAGS) $(LIBS) -o test_client

ConnectionRepository.o: ConnectionRepository.cpp
	$(CXX) -c ConnectionRepository.cpp $(FLAGS)

AIRepository.o: AIRepository.cpp
	$(CXX) -c AIRepository.cpp $(FLAGS)

ChannelWatcher.o: ChannelWatcher.cpp
	$(CXX) -c ChannelWatcher.cpp $(FLAGS)

AIWatcher.o: AIWatcher.cpp
	$(CXX) -c AIWatcher.cpp $(FLAGS)

Connection.o: Connection.cpp
	$(CXX) -c Connection.cpp $(FLAGS)

DistributedObject.o: DistributedObject.cpp
	$(CXX) -c DistributedObject.cpp $(FLAGS)

ClientRepository.o: ClientRepository.cpp
	$(CXX) -c ClientRepository.cpp $(FLAGS)

DValue.o: DValue.cpp
	$(CXX) -c DValue.cpp $(FLAGS)

test_air.o: test_air.cpp
	$(CXX) -c test_air.cpp $(FLAGS)

test_client.o: test_client.cpp
	$(CXX) -c test_client.cpp $(FLAGS)

clean:
	rm *.o
