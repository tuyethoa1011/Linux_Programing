/* Viet mot chuong trinh A tao ra hai tien trinh con B va C.
O tien trinh B, C tai tien trinh con B', C'. Thuc hien ghi noi dung
"Hello, I'm B process" (Doi voi tien trinh B va tuong tu voi cac process
con lai) theo thu tu B' -> C' -> B -> A -> C vao file. O tien trinh
A, dung waitpid() de xac dinh xem khi nao B ket thuc thi ghi vao file)*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/file.h>
#include<sys/wait.h>

//print  PID process print,process status print,... is for debugging

int main()
{	
	pid_t pid_child1,pid_child2,pidB_child,pidC_child;
	pid_t rv1,str_pidB,rv2;
	int status1,status2;
	int fd1, fd2,fd3,fd4,fd5;
	char buf1[22] = {0}, buf2[22] = {0}, buf3[22] = {0}, buf4[22] = {0}, buf5[22] = {0};
	sprintf(buf1,"Hello, I'm B' process\n");
	sprintf(buf2,"Hello, I'm C' process\n");
	sprintf(buf3,"Hello, I'm B process\n");
	sprintf(buf4,"Hello, I'm C process\n");
	sprintf(buf5,"Hello, I'm A process\n");

	pid_child1 = fork();
	

	if(pid_child1 == 0)
	{	
		
		str_pidB = getpid();
		//printf("Child B PID:%d,PPID:%d\n",getpid(),getppid());
		pidB_child = fork();
		if(pidB_child == 0)
		{	
			 fd1=open("./hello.txt",O_RDWR|O_CREAT|O_APPEND,0664);
			 write(fd1,buf1,sizeof(buf1));
		//	printf("Child B' PID:%d,PPID:%d\n",getpid(),getppid());
			exit(0);

		}
		else
		{	
			sleep(2);
			fd3=open("./hello.txt",O_RDWR|O_CREAT|O_APPEND,0664);
			write(fd3,buf3,sizeof(buf3));
			kill(str_pidB,SIGKILL);
			//exit(0);
		}
		
	}
	else
	{
		pid_child2 = fork();
		
		if(pid_child2 == 0)
		{	
			sleep(1);
		//	printf("Child C PID:%d,PPID:%d\n",getpid(),getppid());
			pidC_child = fork();
			if(pidC_child == 0)
			{	

				fd2=open("./hello.txt",O_RDWR|O_CREAT|O_APPEND,0664);
               		       	write(fd2,buf2,sizeof(buf2));
		//		printf("Child C' PID:%d,PPID:%d\n",getpid(),getppid());
				exit(0);
				
			}
			else
			{	
				sleep(2);
				//C job here after checking B end through A

					fd5=open("./hello.txt",O_RDWR|O_CREAT|O_APPEND,0664);
					write(fd5,buf4,sizeof(buf4));
				exit(0);
			}
		}
		else
		{	
	
		//	printf("A father process PID:%d,PPID:%d\n",getpid(),getppid());
			do
			{
				rv1 = waitpid(pid_child1,&status1,0);
				if(rv1 == -1)	
				{
					perror("waitpid");
					exit(EXIT_FAILURE);
				}
				if(WIFEXITED(status1))
				{
		//			printf("Process B exited, status%d\n",WEXITSTATUS(status));
					fd4=open("./hello.txt",O_RDWR|O_CREAT|O_APPEND,0664);
					write(fd4,buf5,sizeof(buf5));
				} else if (WIFSIGNALED(status1))
				{
		//			printf("Process B killed by signal %d\n", WTERMSIG(status));
					fd4=open("./hello.txt",O_RDWR|O_CREAT|O_APPEND,0664);
                                        write(fd4,buf5,sizeof(buf5));
					
				}
				
			}while(!WIFEXITED(status1) && !WIFSIGNALED(status1));
			exit(0);
		}

	}
	while(1);
	return 0;
}
