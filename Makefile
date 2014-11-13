CXX=clang++
FLAGS=-std=c++0x -I. -g
LIBS=-lbamboo -lboost_system

all: ConnectionRepository.o Connection.o AIRepository.o test_air.o ChannelWatcher.o DistributedObject.o AIWatcher.o ClientRepository.o
	$(CXX) test_air.o ConnectionRepository.o AIRepository.o Connection.o ChannelWatcher.o DistributedObject.o AIWatcher.o ClientRepository.o $(FLAGS) $(LIBS) -o test_air

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

test_air.o: test_air.cpp
	$(CXX) -c test_air.cpp $(FLAGS)

clean:
	rm *.o