#include "istream_sck.h"

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0);

//Chat function
void chat_func(int new_sfc)
{
    ssize_t numRead,numBytes;
    char bufrecv[BUF_SIZE];
    char bufsend[BUF_SIZE];
    while(1)
    {
        memset(bufrecv, '0', BUF_SIZE);
        memset(bufsend, '0', BUF_SIZE);

        //Read write cac thu con da dieu o trong day
        printf("Message to server: ");
        fgets(bufsend,BUF_SIZE,stdin);

        if(numBytes=write(new_sfc,bufsend,sizeof(bufsend))==-1)
            handle_error("write()");

         if(numRead=(read(new_sfc,bufrecv,BUF_SIZE))==-1)
            handle_error("read()");

         printf("Response from server: %s", bufrecv);

    }
    close(new_sfc);
}


int main(int argc, char *argv[])
{
    int cfd;
    struct sockaddr_in svaddr,claddr;
    struct hostent *hp;
    //Create client socket
    cfd = socket(AF_INET,SOCK_STREAM,0);
    if(cfd==-1)
        handle_error("socket()");
    
    //Construct server address
    hp = gethostbyname(argv[1]);
    if(hp==0){
        fprintf(stderr,"%s: unknown host\n",argv[1]);
        exit(2); //Exit status 2 appears when there's a permissions problem or a missing keyword in a command or script.
    }

    bcopy(hp->h_addr,&svaddr.sin_addr,hp->h_length);
    //h_addr is is a char pointer and host is a pointer to a struct of type hostent 

    //void bcopy(const void *src, void *dest, size_t n);

    //The bcopy() function copies n bytes from src to dest.  The result
    //is correct, even when both areas overlap.
    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(atoi(argv[2]));

    //Connect to server
    if(connect(cfd,(struct sockaddr*)&svaddr,sizeof(struct sockaddr_in))==-1)
    {
        printf("Connecting to server ERROR\n");
        return 1;
    }

    printf("Client is ready\n");
    
    chat_func(cfd);
    
    return 0;
}