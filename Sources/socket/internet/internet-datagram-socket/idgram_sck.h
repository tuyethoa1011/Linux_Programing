#include<netinet/in.h>
#include<sys/socket.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include <stddef.h>
#include<netdb.h>

#define BUF_SIZE 1024 //Maximum size of messages exchanged between client and server

#define PORT_NUM 50002 //Server port name
