/*Viet mot chuong trinh A tao ra mot tien trinh con B, in ra
PID va PPID cua chung. Su dung system waitpid() de lay duoc trang thai ket thuc
cua tien trinh con B*/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>


int main(int argc, char *argv[])
{
        pid_t pid, rv;
	int status;
        pid = fork();
	
        if(pid >= 0) {
                if(pid==0) { // Child process
                        printf("I'm child process!\n");
                        printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());	
			//try to kill process using kill -9 PID situation
			//while(1); //infinite loop to wait till we kill child process
			//the child kill itself
			//exit(EXIT_SUCCESS); //use exit //same as exit(0) so exit child status will return '0'
			//kill(getpid(), SIGKILL); //use kill //exit child status =  what kind of kill sig you use
 
                } else { // Father process
			do {
				rv = waitpid (pid,&status,0);
			
                        	printf("I'm parent process!\n");
                        	printf("My PID is: %d,my parent PID is: %d\n",getpid(),getppid());
				printf("My child PID is: %d\n",rv);
                        	if(WIFEXITED(status)) { //return true if the child terminated normally
				printf("Child process exit status: %d\n", WEXITSTATUS(status)); //exit status of the child
				}
				if(WIFSIGNALED(status)) { //return true if the child is killed by signal
					printf("Child process is killed by signal %d\n", WTERMSIG(status)); //return the number of the signal that caused the child process to terminate
				}
			
			} while(!WIFEXITED(status) && !WIFSIGNALED(status)); 
                }

        } else {
                printf("fork() unsucessfully\n");
		exit(EXIT_FAILURE);
        }
        return 0;
}

