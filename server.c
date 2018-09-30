#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<string.h>
#include<stdlib.h>
struct data{
int id;
char message[100];
};
int main(){
	struct sockaddr_in serv,cli;
	int sd,sz,nsd;
	char buff[80];
	pid_t pid;
	sd=socket(AF_INET,SOCK_STREAM,0);
	serv.sin_family=AF_INET;
	serv.sin_addr.s_addr=INADDR_ANY;
	serv.sin_port=htons(7791);

	int bind_result=bind(sd,(void *)(&serv),sizeof(serv));
	int listen_result=listen(sd,5);
	sz=sizeof(cli);
	printf("Server Initializing...\nSocket returns :: %d\nBind result:: %d\nListening status :: %d\n",sd,bind_result,listen_result);
	for(;;){
	nsd=accept(sd,(void *)(&cli),&sz);
	if ( (pid = fork()) == 0 ) {
		close(sd);
		struct data d;
		read(nsd,&d,sizeof(d));
		printf("Message Recieve From client :: %s\n",d.message);
		d.id=d.id+5;//just update the value recieved from client to ensure the communication between client and server
		ssize_t s=write(nsd,&d,sizeof(d));
		close(nsd);
		printf("Message  sent to client :: %d\n Write Response %d",d.id,(int)s);
		exit(0);
		}
		close(nsd);
	}
	}


