#include <sys/socket.h>
#include <stddef.h>
#include <stdio.h>
#include<string.h>
#include <sys/un.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
 
#define SV_SOCK_PATH "./socket-dgram"

#define BUF_SIZE 100

int main(int argc, char *argv[])
{	
	struct sockaddr_un svaddr,claddr;
	int sfd,i;
	size_t msgLen;
	ssize_t numBytes;
	char buf[BUF_SIZE];
	char resp[BUF_SIZE];
	socklen_t svaddr_len;

	/*Create client socket; bind to unique pathname(base on PID)*/

	sfd = socket(AF_UNIX,SOCK_DGRAM,0);
	if(sfd==-1) return 1;

	memset(&claddr,0,sizeof(struct sockaddr_un));
	claddr.sun_family = AF_UNIX;
	//create socket for client through pid
	snprintf(claddr.sun_path, sizeof(claddr.sun_path), "./clsocket-dgram.%ld", (long)getpid());
	
	//Bind address
	if(bind(sfd,(struct sockaddr*)&claddr,sizeof(struct sockaddr_un))==-1)
	{
		printf("Bind ERROR\n");
	}

	/*Construct address of server*/

	memset(&svaddr,0,sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path,SV_SOCK_PATH,sizeof(svaddr.sun_path));


	//TUTORIAL: Choose method by deleting 1 of methods comment

	//METHOD1: Enter data in terminal. Ex: ./progam-name hello
	/*msgLen = strlen(argv[2]);
	if(sendto(sfd, argv[2],msgLen,0,(struct sockaddr *)&svaddr, sizeof(struct sockaddr_un)) != msgLen)
		return 1;
	numBytes = recvfrom(sfd, resp, BUF_SIZE, 0, (struct sockaddr*)&svaddr,&svaddr_len);
	if (numBytes == -1)
			return 1;
	else
		printf("Response : %s\n", resp);
	unlink(claddr.sun_path);
	*/ //Need to improve like we need to store more than 1 word	

	//METHOD2: Enter data in a program
	//Send messages to server; echo responses on stdout
	printf("Client is ready to run\n");
	while(1) {

	printf("Message to server: ");
	fflush(stdout); //clear the output buffer

	memset(buf,0,sizeof(buf));
	memset(resp,0,sizeof(resp));
	numBytes = read(STDIN_FILENO,buf,BUF_SIZE);
	
	//remove '/n' in input
	for (i = 0; i < BUF_SIZE; i++) {
            if (buf[i] == '\n') {
                buf[i] = '\0';
            }
        }

	svaddr_len = sizeof(struct sockaddr_un);
	if(numBytes>0)
	{	
		msgLen = strlen(buf);
		//Send msg to server
		if(sendto(sfd,buf,msgLen,0,(struct sockaddr*)&svaddr,sizeof(struct sockaddr_un))!=msgLen) //take raw buffer string input return byte of string as return if read success
		{
			return 1;
		}
	}  else if(numBytes==0){ 
		printf("Nothing to send to server\n"); 
		continue;
	} else if(numBytes==-1) {
		return 1; //sendto error case
	}	
	
	//Read response from server		
	numBytes = recvfrom(sfd,resp,BUF_SIZE,0,(struct sockaddr*)&svaddr,&svaddr_len);

	if(numBytes==-1)
	{
		printf("recvfrom ERROR\n");
		printf("Response %d: %.*s\n",i,(int)numBytes,resp);
	}
	printf("\nMessage received from server: %s\n",resp);

	unlink(claddr.sun_path);	//Remove client socket pathname
	exit(EXIT_SUCCESS);
	}
	return 0;	
}
