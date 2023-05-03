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
	//	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 test micro
	#include "utils_v2.h"

	#define BACKLOG 5

	int initSocketServer(int server_port){
		int sockfd = ssocket(AF_UNIX, SOCK_STREAM, 0);
		int ret = sbind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
		ret = slisten(sockfd, BACKLOG);
	}

	int main(int argc, char const *argv[]){
		int sockfd = initSocketServer(SERVER_PORT);
		printf("Le serveur tourne sur le port : %i \n", SERVER_PORT);
		Zombie zombie= {
			"zombie.c", "127.0.0.1", PORT, sockfd 
		}
		int newsockfd = accept(sockfd, NULL, NULL);

		swrite(newsockfd, *zombie, sizeof(Zombie));

		sclose(sockfd);

		
		// fait un new process
		return 0;
	}

	void process (){
		// lance un bashu avec le nom "programme_inoffensif"
		// change les sortie standard , entrée et erreur au controller 
	}