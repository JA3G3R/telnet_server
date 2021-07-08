#include "socket_funcs.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
void send_to_client(int __fd, char *buffer) {
	int sent;
	sent = send(__fd,buffer,strlen(buffer),0);
	if(sent == -1) {
		fprintf(stderr,"FATAL : while sending: ERROR: %s\n",strerror(errno));
		exit(1);
	}
	while(strlen(buffer)-sent){
		buffer += sent;
		sent = send(__fd,buffer,strlen(buffer),0);
		if(sent == -1) {
                	fprintf(stderr,"FATAL : while sending");
        	        exit(1);
	        }
	}
}
