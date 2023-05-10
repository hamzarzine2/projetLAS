#ifndef header
#define header value
#include <stdbool.h>

#define BACKLOG 10


typedef struct zombie {
	char name [256];
	char ip_address[256];
	int port;
	int sockFd;
	int pid;
} Zombie;


//salam

 static int tabPorts[] = {
 
    3001, 
    3002,
    3003,
    3004,
    3005,
    3006,
    3007,
    3008,
    3009,
    3010
};


int getFreePort(int sockfd);
int validPort(int sockfd,int port);

#endif