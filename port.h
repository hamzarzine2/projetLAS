#ifndef header
#define header value


#define BACKLOG 10




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

//PRE  sockfd : file descriptor number
//
//POST look for a free port and display it
//
//RES show port number
int getFreePort(int sockfd);


//PRE sockfd: file descriptor number
//   port : port to which you want to connect
//
//POST checks if the port is valid and the attribute if any
//
//RES show port number
int isPortFreeAndValid(int sockfd,int port);


#endif