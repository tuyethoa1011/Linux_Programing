#include "ustream_sck.h"
#define BACKLOG 5

int main(int argc,char *argv[])
{   
    struct sockaddr_un svaddr, claddr;
    int sfd,cfd;
    socklen_t claddr_len;
    ssize_t numRead;
    char buf[BUF_SIZE];
    //Create socket
    sfd = socket(AF_UNIX,SOCK_STREAM,0);
    if(sfd==-1) return 1;

    /*Construct server to socket addres, bind socket to it,
    and make this a listening socket*/

    //Before binding address remove the previous created socket
    remove(SV_SOCK_PATH);

    memset(&svaddr,0,sizeof(struct sockaddr_un)); //Clear structure
    svaddr.sun_family = AF_UNIX; //UNIX domain address
    strncpy(svaddr.sun_path,SV_SOCK_PATH,sizeof(svaddr.sun_path)-1);

    //Bind address
    if(bind(sfd,(struct sockaddr*)&svaddr,sizeof(struct sockaddr_un))==-1) {
        printf("Bind ERROR\n");
        return 1;
    }
    
    if(listen(sfd,BACKLOG)==-1)
    {
        printf("Error listening on server\n");
    }


    for(;;){ //Handle client connections iteratively //Iteratively(adv): lap lai lien tuc
        /*Accept a connection. The connection is returned on a new
        socket, 'cfd'; the listening socket ('sfd') remains open 
        and can be used to accept further connection*/
        
        cfd = accept(sfd,(struct sockaddr*)&claddr,&claddr_len);
        if(cfd==-1) {
            printf("Accept ERROR\n");
            return 1;
        }

        /*Transfer data from connected socket to stdout until EOF*/
        while((numRead=read(cfd,buf,BUF_SIZE))>0)
        {
            if(write(STDOUT_FILENO,buf,numRead)!=numRead)
                printf("partial/failed write\n");
        }

        if(numRead==-1)
        {
            printf("Reading data from client ERROR\n");
            return 1;
        }

        if(close(cfd)==-1) {  //close connected client socket to server
            printf("Close ERROR\n");
            return  1;
        }

    }

    return 0;
}