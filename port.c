

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils_v2.h"
#include "port.h"


Port getPortFree();

Port getPortFree(){

	for (int i = 0; i < 10; ++i)
	{
		if(tabPorts[i].isFree == true){
			tabPorts[i].isFree = false;
			return tabPorts[i];
		}
		}

Port port  = {.port = -1, .isFree = false };
return port;
}
