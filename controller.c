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
#include "controller.h"

Zombie* tabZombie;

Zombie* getZombie (int number, char** inputParam){
	tabZombie = (Zombie*)smalloc(number*sizeof(Zombie));
	for (int i = 0; i < number; ++i){
		strcpy(tabZombie[i].name,"Zombie");
		strcpy(tabZombie[i].ip_address, inputParam[i+1]);
	}
	return tabZombie;
}

void done(int sig){
	printf("finito\n");
	printf("id %d\n",tabZombie[0].pid);
	skill(tabZombie[0].pid,SIGINT);
	exit(0);
}


void discussionProcess (void*sock,void* commande,void*numberr){
	int socket=*(int*)sock;
	char* tabCommande = (char*)commande;
	int number = *(int*)numberr;
	printf("ma commande est :: %s \n",tabCommande);
	int size = strlen(tabCommande);
	for (int i = 0; i < number; ++i){
		swrite(tabZombie[i].sockFd,tabCommande,size);
		int numberChar2 = sread(socket,tabCommande,256);
		printf("le resultat est :\n");
		swrite(0,tabCommande,numberChar2);
	}
	printf("j'ai fini\n");
}

int main(int argc, char *argv[])
{	
	ssigaction(SIGINT, done);
	int numberOfZombie = argc-1;
	// cree un socket 
	Zombie* tabZombie = getZombie(numberOfZombie,argv);
	int sockConnect	= ssocket();	

	for (int i = 0; i < numberOfZombie ; ++i){
		  sconnect(argv[i], PORT, sockConnect);
		  sread(sockConnect,&tabZombie[i],sizeof(Zombie));	
	}
		
	char tabCommande [256];
	printf("Veuillez entrez votre commande : \n");
	while(true){
		int i=sread(0,tabCommande,256);
		fork_and_run3(discussionProcess,&sockConnect,&tabCommande,&numberOfZombie);
		printf("Veuillez entrez votre commande : \n");
	}

	sclose(sockConnect);
	// se connecte au zombie entrée en param (test tout les port du header)
	// lis une commande sur stdin et envoie a tout les zombie
	// affiche le contenu lu et les zombie connecter
	// !!! pas de blocant donc utiliser poll
	return 0;
}

