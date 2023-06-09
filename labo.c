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

#include "utils_v2.h"
#include "botNet.h"


int tab[2];
void initZombie(){
	sexecl("./zombie","zombie", NULL);
}

void closeZombies(){
	skill(tab[0],SIGINT);
	skill(tab[1],SIGINT);
	write(0,"Les zombies sont fermés",25 * sizeof(char));
	exit(1);
}

int main(int argc, char const *argv[])
{

	int pidZombie1 = fork_and_run0(initZombie);
	int pidZombie2 = fork_and_run0(initZombie);
	tab[0] = pidZombie1;
	tab[1] = pidZombie2;

	char tab[10];
	while((read(0,tab,10*sizeof(char))) != 0){
	}
	closeZombies();
	return 0;
}