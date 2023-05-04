#ifndef header
#define header value
#include <stdbool.h>

#define PORT 3001
#define BACKLOG 20

typedef struct zombie {
	char name [256];
	char ip_address[256];
	int port;
	int sockFd;
	int pid;
} Zombie;




 int tabPorts[] = {
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


#endif