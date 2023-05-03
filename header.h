#ifndef header
#define header value

#define PORT 3000
#define BACKLOG 20

typedef struct zombie {
	char name [256];
	char ip_address[256];
	int port;
	int sockFd;
} Zombie;

#endif