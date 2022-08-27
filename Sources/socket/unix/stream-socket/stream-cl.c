#include "ustream_sck.h"

int main(int argc, char *argv[])
{   
    int sfd;
    struct sockaddr_un svaddr;
    char buf[BUF_SIZE];
    ssize_t numRead;
    //Create client socket
    sfd = socket(AF_UNIX,SOCK_STREAM,0);
    if(sfd==-1)  return 1;

    /*Construct server address*/
    memset(&svaddr,0,sizeof(struct sockaddr_un)); //Clear structure
    svaddr.sun_family = AF_UNIX; //UNIX domain address
    strncpy(svaddr.sun_path,SV_SOCK_PATH,sizeof(svaddr.sun_path)-1);

    if(connect(sfd,(struct sockaddr*)&svaddr,sizeof(struct sockaddr_un))==-1)
    {
        printf("Connecting to server ERROR\n");
        return 1;
    }

    //Get input 
    numRead = read(STDIN_FILENO,buf,BUF_SIZE);
    /*Copy stdin to socket*/
    if(numRead>0)
    {
        if(write(sfd,buf,numRead)!=numRead)
        {
            printf("Partial/failed write\n");
            return 1;
        }
    }

    if (numRead==-1)
    {
        printf ("Can't read anything from server\n");
    }

    exit(EXIT_SUCCESS); //Close our socket,server see OEF*/
}