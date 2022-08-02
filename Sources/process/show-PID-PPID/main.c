/*Viet mot chuong trinh A  tao ra tien trinh con B roi in ra 
PID va PPID cua chung*/


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{	
	pid_t pid;
	pid = fork();

	if(pid >= 0) {
		if(pid==0) {
			printf("\nI'm child process!\n");
			printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
		} else {
			printf("I'm parent process!\n");
			printf("My PID is: %d\n",getpid());
			while(1);	
		}	

	} else {
		printf("fork() unsucessfully\n");
	}
	return 0;
}
