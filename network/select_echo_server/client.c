#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "my_socket.h"


struct tl
{
	char buff[10];
	int type;
	long long length;
};

int main(int argc, char const *argv[])
{
  int socketfd=Socket(AF_INET,SOCK_STREAM,0);


  struct sockaddr_in serveraddr;
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serveraddr.sin_port = htons(atoi(argv[1]));

  Connect(socketfd,(SA *) &serveraddr,sizeof(SA));

  printf("%s\n", "connect success");
  char buff[1024];
  char readbuff[1024];

  while(1)
  {
  	fgets(buff,1023,stdin);

  	if (strcmp(buff,"quit\n")==0)
	{
		break;
	}

	int ret=write(socketfd,buff,strlen(buff));
	if (ret<0)
	{
		perror("write");
		return 0;
	}

	ret=read(socketfd,readbuff,1024);
	if (ret==0)
	{
		close(socketfd)
		return 1;
	}
	write(1,readbuff,ret);

  }



  close(socketfd);


  return 0;
}






