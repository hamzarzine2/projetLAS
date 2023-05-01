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

int main(int argc, char const *argv[])
{
	// cree un socket 
	// se connecte au zombie entrée en param (test tout les port du header)
	// lis une commande sur stdin et envoie a tout les zombie
	// affiche le contenu lu et les zombie connecter
	// !!! pas de blocant donc utiliser poll

	return 0;
}

void sousProcces (){
	// ecoute et repetition des zombies
}