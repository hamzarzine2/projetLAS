#ifndef header
#define header value
#include <stdbool.h>

#define PORT 3025
#define BACKLOG 20

typedef struct zombie {
	char name [256];
	char ip_address[256];
	int port;
	int sockFd;
	int pid;
} Zombie;


typedef struct port {
	int port;
	bool isFree;
} Port;

Port tabPorts[10] = {
	{3001, true},
    {3002, true},
    {3003, true},
    {3004, true},
    {3005, true},
    {3006, true},
    {3007, true},
    {3008, true},
    {3009, true},
    {3010, true}
};


Port getPortFree();

#endif