#include "idgram_sck.h"

/*
 The form of the command line is:
 * <programname> <hostname> <portnumber>
 */

int main(int argc,char *argv[])
{
    struct sockaddr_in svaddr,claddr;
    int sfd;
    ssize_t numBytes;
    size_t msgLen;
    char buf[BUF_SIZE];
    char resp[BUF_SIZE];
    int i;
    socklen_t len;
    struct hostent *hp;

    //Create client socket
    sfd = socket(AF_INET,SOCK_DGRAM,0);
     if(sfd==-1) {   
        printf("socket created ERROR\n");
        return 1;
    }
  
    /*
     * Construct name, with no wildcards, of the socket to send to.
     * Gethostbyname() returns a structure including the network address
     * of the specified host.  The port number is taken from the command
     * line.
     */

    hp = gethostbyname(argv[1]);
    if(hp==0){
        fprintf(stderr,"%s: unknown host\n",argv[1]);
        exit(2);
    }

    bcopy(hp->h_addr,&svaddr.sin_addr,hp->h_length);
    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(atoi(argv[2]));

    printf("Client is ready");
	
    memset(resp,0,sizeof(resp));
    memset(buf,0,sizeof(buf));

    printf("\nSend message to server: ");
    
    fflush(stdout);
  
	numBytes = read(STDIN_FILENO,buf,BUF_SIZE);
	
	//remove '/n' in input
	for (i = 0; i < BUF_SIZE; i++) {
            if (buf[i] == '\n') {
                buf[i] = '\0';
            }
        }

    //Send messages to server; echo responses to stdout
    if(numBytes>0){
        msgLen = strlen(buf);
        if(sendto(sfd,buf,msgLen,0,(struct sockaddr*)&svaddr,sizeof(struct sockaddr_in))!=msgLen)
        {
            perror("sending datagram message\n");
        }
    } else if(numBytes==0) {
        perror("No data was sent\n");
        return 1;
    } else if(numBytes==-1) {
        perror("sendto unsuccessfully\n");
        return 1;
    }

	//Read response from server		
	numBytes = recvfrom(sfd,resp,BUF_SIZE,0,(struct sockaddr*)&svaddr,&len);

	if(numBytes==-1)
	{
		printf("recvfrom ERROR\n");
		return 1;
	}
	printf("\nMessage received from server: %s\n",resp);
    

    close(sfd); //Close connection of client to server 
    return 0;
}
