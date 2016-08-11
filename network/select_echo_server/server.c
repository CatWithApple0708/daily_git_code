#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "my_socket.h"
#include <sys/socket.h>
#include <sys/select.h>


int dothing(int socket);
ssize_t
Inet_Write(int fildes, const void *buf, size_t nbyte);


/******************************************************************************/

int main(int argc, char const *argv[])
{
  int socketfd=Socket(AF_INET,SOCK_STREAM,0);


  struct sockaddr_in serveraddr, clientaddr;
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr("0.0.0.0");
  serveraddr.sin_port = htons(atoi(argv[1]));

  Bind(socketfd,(SA *) &serveraddr,sizeof(SA));

  Listen(socketfd,10);

  fd_set orig;
  fd_set copy;
  int maxnfds=1023;

  FD_ZERO(&orig);
  FD_SET(0, &orig);
  FD_SET(socketfd, &orig);

  FD_COPY(&orig,&copy);



  while(1)
  {
  	FD_COPY(&orig,&copy);
  	if (select(maxnfds,&copy,NULL,NULL,NULL)==-1)
  	{
  		perror("select");
  		return -1;
  	}
  	// printf("hello\n");
  	for (int i = 0; i < maxnfds+1; ++i)
  	{
  		if (FD_ISSET(i,&copy))
  		{
	  		if (i==socketfd)
	  		{
	  			int clientfd=Accept(socketfd,NULL,NULL);
	  			FD_SET(clientfd, &orig);
	  			printf("accept%d\n", i);
	  		}
	  		else
	  		{
	  			printf("read%d\n", i);
	  			char buff[1024];
	  			int ret=read(i,buff,sizeof(buff)-1);
	  			if (ret<0)
	  			{
	  				perror("read socketfd failure");
	  				close(i);
	  				FD_CLR(i,&orig);
	  				continue;
	  			}
	  			else if (ret==0)
	  			{
	  				close(i);
	  				FD_CLR(i,&orig);
	  				continue;
	  			}
	  			else
	  			{
	  				if(Inet_Write(i,buff,ret)<0){/*error process*/}
	  			}
	  		}
  		}

  	}


	// printf("I got a clientfd %d\n",clientfd);

	// dothing(clientfd);
  }

  close(socketfd);
  return 0;
}


/******************************************************************************/

int dothing(int socket)
{
	int buff[1024];

	while(1)
	{
		int ret=read(socket,&buff,1024);
		if (ret<=0)
		{
			return 1;
		}
		write(socket,&buff,ret);
	}

	return 1;
}


ssize_t
Inet_Write(int fildes, const void *buf, size_t nbyte)
{
	int haswrite=0;
	while(1)
	{
		int ret=write(fildes,buf,nbyte-haswrite);
		if (ret<0)
		{
			perror("write failure");
			return -1;
		}
		haswrite+=ret;
		if (haswrite==nbyte)
		{
			return haswrite;
		}
	}
}










