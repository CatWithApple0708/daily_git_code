#ifndef MY_SOCKET_H
#define MY_SOCKET_H


typedef struct sockaddr SA;


static inline  void error_process(const char * message)
{
	perror(message);
	exit(EXIT_FAILURE);
}


int
Socket(int domain, int type, int protocol);

int
Bind(int socket, const struct sockaddr *address, socklen_t address_len);

int
Listen(int socket, int backlog);

int
Accept(int socket, struct sockaddr * address, socklen_t * address_len);

int
Connect(int socket, const struct sockaddr *address, socklen_t address_len);


//在发送端没有关闭socke之前，可以接受完成的数据
// ssize_t
// Inet_read(int fildes, void *buf, size_t nbyte);


#endif