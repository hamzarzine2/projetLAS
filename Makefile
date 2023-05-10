CC=gcc

CCFLAGS=-D_DEFAULT_SOURCE -D_XOPEN_SOURCE -D_BSD_SOURCE -std=c11 -pedantic -Wvla -Wall -Werror

ALL = zombie controller labo

all: $(ALL)

port.o: port.c port.h
	$(CC) $(CCFLAGS) -c port.c

zombie : zombie.o utils_v2.o port.o
	$(CC) $(CCFLAGS) -o zombie zombie.o utils_v2.o port.o
zombie.o: zombie.c botNet.h
	$(CC) $(CCFLAGS) -c zombie.c


controller : controller.o utils_v2.o port.o
	$(CC) $(CCFLAGS) -o controller controller.o utils_v2.o port.o
controller.o: controller.c botNet.h
	$(CC) $(CCFLAGS) -c controller.c


labo : labo.o utils_v2.o
	$(CC) $(CCFLAGS) -o labo labo.o utils_v2.o 
labo.o: labo.c botNet.h
	$(CC) $(CCFLAGS) -c labo.c


utils_v2.o: utils_v2.c utils_v2.h
	$(CC) $(CCFLAGS) -c utils_v2.c



clean:
	rm -f *.o
	rm -f $(ALL)		

