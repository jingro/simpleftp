CXXFLAGS += -std=c++11
client_objects = socket.o client_socket.o client_cmd_executor.o client.o cmd_executor.o
server_objects = socket.o server_socket.o server_cmd_executor.o server.o cmd_executor.o


all : client server

client : $(client_objects)
	g++ -o client $(client_objects) -lpthread

server : $(server_objects)
	g++ -o server $(server_objects) -lpthread


.PHONY : clean
clean:
	rm -f *.o server client
