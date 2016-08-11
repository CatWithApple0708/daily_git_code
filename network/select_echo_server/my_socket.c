#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/uio.h>
#include  <stdlib.h>
#include <unistd.h>
#include "my_socket.h"


int
Socket(int domain, int type, int protocol)
{
    int ret=socket(domain, type, protocol);
    if (ret<0)
    {
      error_process("socket failure");
      return -1;
    }
    return ret;
}


int
Bind(int socket, const struct sockaddr *address, socklen_t address_len)
{
	int ret=bind(socket,address,address_len);
	if (ret<0)
	{
		error_process("bind failure");
		return -1;
	}
	return ret;

}

int
Listen(int socket, int backlog)
{
	int ret=listen(socket,backlog);
	if (ret<0)
	{
		error_process("listen failure");
		return -1;
	}
	return ret;

}

int
Accept(int socket, struct sockaddr * address, socklen_t * address_len)
{
	int ret=accept(socket,address,address_len);
	if (ret<0)
	{
		error_process("accept failure");
		return -1;
	}
	return ret;
}



int
Connect(int socket, const struct sockaddr *address, socklen_t address_len)
{
	int ret=connect(socket,address,address_len);
	if (ret<0)
	{
		error_process("connect failure");
		return -1;
	}
	return ret;

}


// ssize_t
// Inet_read(int fildes, void *buf, size_t nbyte)
// {
// 	ssize_t hasread=0;
// 	while(1)
// 	{
// 		int ret=read(fildes,buf,nbyte-hasread);
// 		if (ret==0)
// 		{
// 			return hasread;
// 		}
// 		if (ret<0)
// 		{
// 			// error_process("read");
// 			perror("read:");
// 			return -1;
// 		}
// 		hasread+=ret;
// 		if (hasread==nbyte)
// 		{
// 			return hasread;
// 		}
// 	}
// }
