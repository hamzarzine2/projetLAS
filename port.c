#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/socket.h>

#include "utils_v2.h"
#include "port.h"



int getFreePort(int sockfd);
int validPort(int sockfd,int port);

int getFreePort(int sockfd){
	
  	
	for (int i = 0; i < 10; ++i)
	{
	struct sockaddr_in addr;  
  	memset(&addr,0,sizeof(addr));
  	addr.sin_family = AF_INET;
  	addr.sin_port = htons(tabPorts[i]);
 	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
	if(ret != -1)
		return tabPorts[i];
	}

	perror("Tous les ports sont utilisées");
  	exit(1);
}

int validPort(int sockfd,int port){

for (int i = 0; i < 10; ++i)
	{
		if(port == tabPorts[i])
		{
			struct sockaddr_in addr;  
  			memset(&addr,0,sizeof(addr));
  			addr.sin_family = AF_INET;
  			addr.sin_port = htons(port);
 			addr.sin_addr.s_addr = htonl(INADDR_ANY);
			int ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
			if(ret != -1)
				return tabPorts[i];
		}	

	}

	perror("Votre port est invalide(pas dans la liste des 10");
  	exit(1);

}