/*Kiem tra SIGINT co bi block trong process hay khong.
Neu khong thuc hien block/unblock thu SIGINT*/
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void static handler(int sig_num)
{
	if(sig_num==SIGINT)
	{
		printf("\nCaught SIGINT\n");
		exit(EXIT_SUCCESS);
	}
}


int main(int argc,char *argv[])
{	
	sigset_t newset,oldset; //oldset: present set, newset: set after changed
	int choose=0, temp = 0;

	sigemptyset(&newset); //Initialize signal mask set
	sigemptyset(&oldset);
	

	while(choose!=1 && choose !=2){
		printf("--------- SIGNAL SIMULATION ----------\n");
		printf("1. Process with unblocked SIGINT\n2. Process with blocked SIGINT\n");
		printf("Choose mode: ");
		scanf("%d",&choose);
		
	if(choose==2)
	{
		sigaddset(&newset,SIGINT); //Them SIGINT vao signal mask*
	} //choose = 2 do nothing 
		--temp;
		if(temp<0)
		{	
			printf("Please enter again! We just have 2 options\n");
		}
		if(temp == -50) { 
			printf("ERROR! You attempts too many times\n");
			printf("System have to stop program\n");
			kill(getpid(),SIGQUIT);
			exit(EXIT_FAILURE); //50 tries to enter option, still wrong?? then the program will be core dump
		} 	
	}

	if (signal(SIGINT, handler) == SIG_ERR) {
                fprintf(stderr, "Cannot handle SIGINT\n");
                exit(EXIT_FAILURE);
        }

	if(sigprocmask(SIG_SETMASK,&newset,&oldset)==0)  //sigprocmask successfully
	{
		if(sigismember(&newset,SIGINT)==1)
		{
			printf("SIGINT is blocked\n");
			sigdelset(&newset,SIGINT); //Unblocked SIGINT
			sigprocmask(SIG_SETMASK, &newset, &oldset); //Update signal mask
			printf("SIGINT is unblocked\n");
		}
		else if (sigismember(&newset,SIGINT)==0)
		{	

			printf("SIGINT is unblocked\n");
			sigaddset(&newset,SIGINT); //Add SIGINT into signal mask		
			sigprocmask(SIG_SETMASK, &newset, &oldset); //Update signal mask
			printf("SIGINT has blocked now\n");}
		
	} else {
		perror("sigprocmask");
	}

	for(;;); //Loop forever
	pause(); //Block until a signal is caught
	return 0;
}
