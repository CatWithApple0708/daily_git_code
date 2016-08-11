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



int dothing(int socket);


/******************************************************************************/

int main(int argc, char const *argv[])
{
  int socketfd=Socket(AF_INET,SOCK_STREAM,0);


  struct sockaddr_in serveraddr, clientaddr;
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serveraddr.sin_port = htons(atoi(argv[1]));

  Bind(socketfd,(SA *) &serveraddr,sizeof(SA));

  Listen(socketfd,10);

  while(1)
  {
 	int clientfd=Accept(socketfd,NULL,NULL);
	printf("I got a clientfd %d\n",clientfd);

	dothing(clientfd);

  	close(clientfd);
  }


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











