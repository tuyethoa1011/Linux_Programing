#include "idgram_sck.h"

int main(int argc, int *argv[])
{   
    struct sockaddr_in svaddr,claddr;
    int sfd,i;
    socklen_t len;
    ssize_t numBytes;
    char buf[BUF_SIZE];
    char claddrStr[INET_ADDRSTRLEN];

    sfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sfd==-1) 
    {   
        printf("socket created ERROR\n");
        return 1;
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
        printf("Bind error exit\n");
        return 1;
    }
    printf("Server is ready\n");
    /*Receive messages, convert to upper case*/
    for(;;)
    {
        //Find assigned port value and print it out
        len = sizeof(struct sockaddr_in);
        if(getsockname(sfd,(struct sockaddr*)&svaddr,&len)==-1)
        {   
            perror("getting socket name\n");
            exit(1);
        }

        printf("\nServer socket has port #%d\n",ntohs(svaddr.sin_port));


        numBytes = recvfrom(sfd,buf,BUF_SIZE,0,(struct sockaddr*)&claddr,&len);

        if(numBytes==-1)
        {
            printf("Exit recvfrom error\n");
            return 1;
        }

        if(inet_ntop(AF_INET,&claddr.sin_addr,claddrStr,INET_ADDRSTRLEN)==NULL)
        {
            printf("Couldn't convert client address to string\n");
        } else printf("Server received %ld bytes from (%s,%u)\n",(long int)numBytes,claddrStr,ntohs(claddr.sin_port));
        //ntohs() translates an unsigned short integer into host byte order.
        //"Host byte order", on the other hand, sorts bytes in the manner which is most natural to the host software and hardware
        //For more information: https://www.ibm.com/docs/ja/zvm/7.2?topic=domains-network-byte-order-host-byte-order

        printf("Data sent from client: %s\n",buf);

        for(i=0;i<numBytes;i++)
        {
            buf[i] = toupper((unsigned char)buf[i]);
        }

        printf("\nSend back to client: %s\n", buf);
        if(sendto(sfd,buf,numBytes,0,(struct sockaddr*)&claddr,len)!=numBytes)
        {
            printf("Fatal sendto\n");
            return 1;
        }

    }
    return 0;
}
