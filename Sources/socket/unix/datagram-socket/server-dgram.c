#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stddef.h>
#include <stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>



#define SV_SOCK_PATH "./socket-dgram"

#define BUF_SIZE 100

int main(int argc, char *argv[])
{	
	struct sockaddr_un svaddr, claddr;
	int sfd, i;
	ssize_t numBytes;
	socklen_t claddr_len;
	char buf[BUF_SIZE];
	char resp[BUF_SIZE];

	sfd = socket(AF_UNIX,SOCK_DGRAM,0); //Create server socket
	if(sfd==-1)
	{
		return 1;
	}

	memset(&claddr,0,sizeof(struct sockaddr_un));
	claddr.sun_family = AF_UNIX;

	remove(SV_SOCK_PATH);
	/*Construct well-known address and bind server socket to it*/

	memset(&svaddr,0,sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path,SV_SOCK_PATH,sizeof(svaddr.sun_path)-1);

	
	//Bind address
	if(bind(sfd,(struct sockaddr*)&svaddr,sizeof(struct sockaddr_un))==-1)
	{
		printf("Bind ERROR\n");
	}

	printf("Start listening on server\n");

	/*Receive messages and return to client*/
	while(1)
	{	
		memset(buf,0,sizeof(buf));
		claddr_len = sizeof(struct sockaddr_un);
		numBytes = recvfrom(sfd,buf,BUF_SIZE,0,(struct sockaddr*)&claddr,&claddr_len);

		if(numBytes==-1)
			printf("recvfrom ERROR\n");

		
		
		printf("Server received %ld bytes from %s\n",(long int)numBytes,claddr.sun_path);																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																											
	

		printf("Message received from client: %s\n",buf);

		// Uppercase received characters:
        for (i = 0; i < numBytes; i++) {
            buf[i] = toupper((unsigned char)buf[i]);
        }

        // Send back uppercase-ed characters to client:
        printf("Send back to client: %s\n", buf);
        if (sendto(sfd, buf, numBytes, 0, (struct sockaddr *) &claddr, claddr_len) != numBytes) {
            exit(EXIT_FAILURE);
        }
    }
	return 0;

}
