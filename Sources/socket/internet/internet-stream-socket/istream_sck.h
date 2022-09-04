#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<netdb.h>
#include<unistd.h>
#include <string.h>
#include<stdlib.h>
#include<unistd.h>

#define BUF_SIZE 1024 //Maximum size of messages exchanged between client and server

#define PORT_NUM 8000//Server port name