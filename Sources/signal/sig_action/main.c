/*Viet chuong trinh in ra thong diep bat ki khi nhan to hop phim
CTRL + C. Dang ki action cho SIGSUR1 va SIGSUR2*/

//BONUS: Thu dung SIGUSR de dinh nghia dang ky action bao SIGCHLD cho process cha
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

pid_t pid;

static void sig_handler(int sig_num)
{
	printf("\nHoa is studying Linux Programing - SIGINT DETECTED\n");
}

static void handler_sigusr(int sig_num)
{
	if(sig_num==SIGUSR1) //Action terminated
	{
		printf("\nHello! I'm SIGUSR1, let's terminate the program\n");
		kill(pid,SIGTERM);
	}
	else if(sig_num==SIGUSR2) //Action exit
	{
		printf("\nHello! I'm SIGUSR2, it's time to exit this program\n");
		exit(EXIT_SUCCESS);
	}
}


int main(int argc, char *argv[])
{	
	pid = getpid();
	//Dang ky action cho CTRL + C	
	signal(SIGINT,sig_handler);

	//Dang ky action cho SIGUSR1 va SIGUSR2
	signal(SIGUSR1,handler_sigusr);
	signal(SIGUSR2,handler_sigusr);

	while(1); //loop forever :))
	return 0;
}

