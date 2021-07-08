#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "socket_funcs.h"
int read_from_client(int fd,char buffer[]) {
	int recvd = recv(fd,buffer,1024,0);
	if(recvd == -1){
		fprintf(stderr,"FATAL : while recieving data\n");
		exit(1);
	}
	int to_receive = 1024-recvd;
	while(buffer[recvd-1] != '\n'){
		recvd = recv(fd,buffer,to_receive,0);
        if(recvd == -1){
                fprintf(stderr,"FATAL : while recieving data\n");
                exit(1);
        }
	to_receive -= recvd;
	}
	return recvd;
}
