#ifndef header
#define header value
#include <stdbool.h>

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
   4002,
   5003,
   6004,
   8005,
   3076,
   5337,
   6008,
   6009,
   7010
};


#endif