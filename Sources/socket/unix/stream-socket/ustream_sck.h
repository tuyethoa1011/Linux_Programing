#include<stdio.h>
#include<sys/un.h>
#include<sys/socket.h>
#include<ctype.h>
#include<unistd.h>
#include<stdlib.h>

#define SV_SOCK_PATH "./us_socket"

#define BUF_SIZE 1000