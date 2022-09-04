#include "istream_sck.h"

#define BACKLOG 5 //Maximum client connect to server

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0);

//Chat function
void chat_func(int new_sfc,char claddrStr[INET_ADDRSTRLEN])
{
    ssize_t numRead,numBytes;
    char buf[BUF_SIZE];
    char resp[BUF_SIZE];
    while(1)
    {
        memset(buf, '0', BUF_SIZE);
        memset(resp, '0', BUF_SIZE);

        if(numRead=(read(new_sfc,buf,BUF_SIZE))==-1)
            handle_error("read()");
        //clear man hinh server
        if(strncmp("exit",buf,4)==0)
        {
            system("clear");
            break;
        }

        printf("\nMessage from client (%s): %s\n",claddrStr,buf);

        //Response from server
        printf("Response back to message: ");
        fflush(stdin);
        fgets(resp,BUF_SIZE,stdin);
        
        if(numBytes = write(new_sfc,resp,sizeof(resp))==-1)
            handle_error("write()");
        
        if(strncmp("exit",resp,4)==0)
        {
            system("clear");
            break;
        }
        
    }
    close(new_sfc);
}

int main(int argc, char *argv[])
{
    //Initialize vars
    struct sockaddr_in svaddr,claddr;
    int sfd,cfd;
    char claddrStr[INET_ADDRSTRLEN];
    socklen_t len;
    

    //Create server socket
    sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd==-1){
        perror("socket created error\n");
        exit(1);
    }

   //Construct server address
    memset(&claddr,0,sizeof(struct sockaddr_in));
    memset(&svaddr,0,sizeof(struct sockaddr_in));

    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(PORT_NUM); 
    //Network byte order is defined to always be big-edian
    //htons() translates an unsigned short integer into network byte order.
    svaddr.sin_addr.s_addr = INADDR_ANY; //automatically get IP-addr (Wild card address)
    //bind() of INADDR_ANY does NOT "generate a random IP". It binds the socket to all available interfaces.
    
    if(bind(sfd,(struct sockaddr*)&svaddr,sizeof(struct sockaddr_in))==-1)
    {
        printf("bind error exit\n");
        return 1;
    }

     //Find assigned port value and print it out
    len = sizeof(struct sockaddr_in);
    if(getsockname(sfd,(struct sockaddr*)&svaddr,&len)==-1)
    {   
        perror("getting socket name\n");
        exit(1);
    }

    printf("Server socket has port #%d\n",ntohs(svaddr.sin_port));

    if(listen(sfd,BACKLOG)==-1)
    {
        printf("Error listening on server\n");
    }
    
    //Show infor client vua nghe duoc


    while(1) //forever while true loop
    {
        len = sizeof(struct sockaddr_in);
        cfd = accept(sfd,(struct sockaddr*)&claddr,&len);

        if(cfd==-1)
        {
            perror("accept error\n");
            continue;
        }

        printf("Accepted connection\n");
        //Server accepted connection
         if(inet_ntop(AF_INET,&claddr.sin_addr,claddrStr,INET_ADDRSTRLEN)==NULL)
        {
            printf("Couldn't convert client address to string\n");
        } else printf("Server accepted connect from (%s,%u)\n",claddrStr,ntohs(claddr.sin_port));

        chat_func(cfd,claddrStr);

        

    }
    close(sfd);
    return 0;
}