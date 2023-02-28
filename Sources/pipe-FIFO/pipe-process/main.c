
//Bai 2: Tao pipe. Gui nhan du lieu giua cac related process

//Parent dong vai tro writer
//Child dong vai tro reader

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main()
{	
	int filedes[2]; //file descriptor store for pipe
	char *message = "Learning Pipe ^-^";
	char read_buf[128];
	int nbytes;
	
	pipe(filedes);

	pid_t  pid = fork(); //create child process here
	
	if(pid == 0)
	{	
		//Phan xu ly process con
		close(filedes[1]);
		//read in a string from a pipe
		nbytes = read(filedes[0],read_buf,sizeof(read_buf));
		read_buf[nbytes] = 0; //terminate the string
		printf("Read string: %s\n", read_buf);
		exit(0);
	} else if (pid > 0)
	{	
		//Phan xu ly process cha
		close(filedes[0]); //Parent process does not need this end of pipe
		write(filedes[1],message,strlen(message));
	} else { perror ("Error fork()\n"); exit(1); }
	return 0;
}
