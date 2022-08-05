#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int signum)
{
	printf("I'm in handler()\n");
	wait(NULL);	//wait(NULL) will block parent process until any of its children finished
}

int main()
{
	pid_t child_pid = fork();
	
	if(child_pid >= 0)
	{
		if(child_pid==0)
		{
			printf("I am Child, myPID: %d\n",getpid());
			while(1);

		}
		else 
		{	
			/* When a child is terminated, a corresponding SIGCHLD signal
				is delivered to parent*/
			signal(SIGCHLD, handler);
			printf("I'm Parent\n");
			while(1);
		}

	}
	else
	{
		printf("fork() unsucessfully\n");
	}



	return 0;
}
