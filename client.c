#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include<string.h>
struct data{
  int id;
 char message[100];
 };


int main(){
	struct sockaddr_in serv,cli;
	int sd;
	char buff[80];
	struct data d;
	char *ip_addr="172.16.132.56";
	sd=socket(AF_INET,SOCK_STREAM,0);
	serv.sin_family=AF_INET;
	serv.sin_addr.s_addr=inet_addr (ip_addr);
	serv.sin_port=htons(7791);
	int result=connect(sd,(void *)(&serv),sizeof(serv));
	

	printf("connection status :: %d\nEnter message sent to server :: \n",result);
	fgets(d.message,100,stdin);
	printf("Enter Sequence No \n");
	scanf("%d",&d.id);
	printf("Message Sending to Server :: %s\n",d.message);
	ssize_t s=write(sd,&d,sizeof(d));
	ssize_t r=read(sd,&d,sizeof(d));
	printf("Message From Server :: %s\n Sequence No %d\nread status %d",d.message,d.id,(int)r);
	}


