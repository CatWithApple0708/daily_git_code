all: server client

server:server.c my_socket.h my_socket.c
	gcc -o server server.c my_socket.c
client:client.c my_socket.h my_socket.c
	gcc -o client client.c my_socket.c