#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "dump.h"
#include "socket_funcs.h"
#define PORT 7891
void error(char *msg) {
	fprintf(stderr,"FATAL : %s\n",msg);
	//exit(1);
}
int main() {
	struct sockaddr_in local_sock,remote_sock; 
	int fd, new_fd,yes=1;
	if((fd = socket(PF_INET,SOCK_STREAM,0))==-1)
		error("while opening socket");
	if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,(char*)&yes,sizeof(int))==-1)
		error("While setting socket option SO_REUSEADDR");
	local_sock.sin_addr.s_addr=0;
	local_sock.sin_port=htons(PORT);
	local_sock.sin_family=PF_INET;
	if(bind(fd, (struct sockaddr*)(&local_sock),sizeof(local_sock))==-1)
		error("while binding to socket");
	if(listen(fd,10)==-1)
		error("while listening on socket");
	int sock_size=sizeof(struct sockaddr);
	while(1)
	{
		new_fd = accept(fd,(struct sockaddr*)&local_sock,&sock_size);
		if(new_fd==-1)
			error("while accepting connection");
		pid_t pid = fork();
		if(!pid)
		{
			close(fd);
			printf("Connected to %s\n",inet_ntoa(remote_sock.sin_addr));
        		send_to_client(new_fd,"Hello World\n");
			int recv_length;
			char buffer[1024];
			recv_length=read_from_client(new_fd,buffer);	
			printf("RECV : %d bytes data\n",recv_length);
			dump(buffer,recv_length);
			while(recv_length>0){
				recv_length=read_from_client(new_fd,buffer);
				printf("RECV : %d bytes data\n",recv_length);
	        	        dump(buffer,recv_length);
				recv_length -= 2;
			
			}
			shutdown(new_fd,SHUT_RDWR);
			close(new_fd);
			return 1;
		}
		close(new_fd);
	}	
	
}	
	
