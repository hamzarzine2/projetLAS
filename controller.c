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
#include "header.h"

int initSock(Zombie* zombie){
	int sock = ssocket();	
	zombie->port = PORT;
	  	printf("OFF\n");

  	sconnect(zombie->ip_address, zombie->port, sock);
  	zombie->sockFd=sock;
  	return sock;
}

Zombie* getZombie (int number, char** inputParam){
	Zombie* tabZombie = (Zombie*)smalloc(number*sizeof(Zombie));
	for (int i = 0; i < number; ++i){
		strcpy(tabZombie[i].name,"Zombie");
		strcpy(tabZombie[i].ip_address, inputParam[i+1]);
	}
	return tabZombie;
}

int main(int argc, char *argv[])
{	
	int numberOfZombie = argc-1;
	// cree un socket 
	Zombie* tabZombie = getZombie(numberOfZombie,argv);
	for (int i = 0; i < numberOfZombie ; ++i){
		int sockConnect = initSock(&tabZombie[i]);

		printf("sock !! %d\n", sockConnect);
	}
	// se connecte au zombie entrée en param (test tout les port du header)
	// lis une commande sur stdin et envoie a tout les zombie
	// affiche le contenu lu et les zombie connecter
	// !!! pas de blocant donc utiliser poll
	return 0;
}

void sousProcces (){
	// ecoute et repetition des zombies
}