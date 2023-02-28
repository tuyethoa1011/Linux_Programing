
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	int filedes; //filedes for fifo
	char buffer[128],read_buf[128];
	
	char *myFIFO = "./helloFIFO";	
	if(mkfifo(myFIFO,0666) == -1)
	{
		perror("FIFO create failed!\n");
	}
	
	pid_t pid = fork(); //create child process
	
	if(pid == -1) {
		perror("fork");
	} else if(pid == 0) {
		//child process
		filedes = open(myFIFO,O_RDONLY);
		read(filedes,read_buf,128);
		printf("Recieved string from parent process: %s", read_buf);
		close(filedes);
		exit(0);
	} else if (pid > 0) {
		//father process
		filedes = open(myFIFO,O_WRONLY);
		printf("Write something: ");
		fgets(buffer,128,stdin);
		
		write(filedes, buffer,strlen(buffer));	
		close(filedes);
	
	}
	return 0;
}
