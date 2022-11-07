# Copyright Frederick Levins, 2022

socket: PracticalSocket.o
	g++ -Wall -c PracticalSocket.h PracticalSocket.o

server: PracticalSocket.o
	g++ -o server Server.cpp PracticalSocket.o

client: PracticalSocket.o
	g++ -o client Client.cpp PracticalSocket.o

clean:
	rm *.o

cpplint-server: server
	cpplint Server.h Server.cpp

run-server: server
	./server 1750

cpplint-client: client
	cpplint Client.cpp

run-client: client
	./client localhost 1750