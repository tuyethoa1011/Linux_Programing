//Bai 1: Tao pipe. Doc ghi du lieu su dung pipe vua tao

#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int  main()
{
	int n;
	int filedes[2];
	
	char buffer[256];
	char *message = "Hello, World!";

	pipe(filedes); 

	write(filedes[1], message, strlen(message));

	if((n = read (filedes[0], buffer, 256)) >= 0) {
		buffer[n] = 0; //terminate the string
		printf("Read %d bytes from the pipe: %s\n",n,buffer);
	}	
	else perror ("read");
	exit(0);
}
