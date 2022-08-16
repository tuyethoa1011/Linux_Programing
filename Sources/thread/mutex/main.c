/*Viet mot chuong trinh thuc hien tao 3 threads.
	. Thread thu nhat thuc hien viec nhap du lieu sinh
	  vien tu ban phim, bao gom thong tin: Ho ten, 
	  ngay sinh, que quan.
	. Moi lan nhap xong du lieu mot sinh vien, thread thu hai
	  se ghi thong tin sinh vien do vao file (moi thong tin
	  sinh vien nam tren 1 dong)
	. Thread thu 3 se doc du lieu vua ghi duoc va in ra terminal
	  roi thong bao cho thread 1 tiep tuc nhap them sinh vien.
 Su dung mutex va condition variable de giai quyet bai toan*/


#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

int counter;
int fd1,fd2,fd3;
pthread_t threadid1, threadid2, threadid3;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER,cond2 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;



typedef struct
{
	char name[70]; //student's name
	char date[20]; //date of birth format dd/mm/yyyy
	char hmtwn[50]; //Hometown name

} student; //student's information struct

static void *thr_handle1(void *argvs) //thread 1 dung de nhap lieu thong tin
{
	student *data = (student*) argvs;

	pthread_mutex_lock(&lock);

	
	while(1){
		pthread_cond_wait(&cond,&lock);

		if (counter==0)
		{	
			//clear previous data
			memset(data->name,0,sizeof(data->name));
			memset(data->date,0,sizeof(data->date));
			memset(data->hmtwn,0,sizeof(data->hmtwn));

			printf("--------- INSERT STUDENT'S INFORMATION ---------\n");
			printf("Name: ");
			fgets(data->name,sizeof(data->name),stdin);
			printf("Birth time(dd/mm/yyyy): ");
			fgets(data->date,sizeof(data->date),stdin);
			printf("Home town: ");
			fgets(data->hmtwn,sizeof(data->hmtwn),stdin);
		
			++counter;
		}


		pthread_cond_signal(&cond2);

		pthread_mutex_unlock(&lock);	
	
	}	
}

static void *thr_handle2(void *argvs)
{
		student *data = (student*) argvs;
		
		pthread_mutex_lock(&lock);
		//create file
		while(1){
		
		pthread_cond_wait(&cond2,&lock);

		if(counter==1) {
		
		int length1 = sizeof(data->name); //name string length
		int length2 = sizeof(data->date); //birth date string length
		int length3 = sizeof(data->hmtwn); //Hometown string length

		int real1=0,real2=0,real3=0;

		for(int i = 0;i<length1;i++)
		{	
			if(data->name[i]!='\0')
			{	
				++real1;
			}
			if(data->name[i]=='\n')
			{
				data->name[i] = ' ';
			}
		}
		
		if((fd1=open("./infor.txt",O_RDWR|O_CREAT|O_APPEND,0664))==-1)
		{
			printf("create file infor.txt error\n");
		}
	
		write(fd1,data->name,real1);
		
		for(int i = 0;i<length2;i++)
		{	
			if(data->date[i]!='\0')
			{	
				++real2;
			}
			if(data->date[i]=='\n')
			{
				data->date[i] = ' ';
			}
		}

		if((fd2=open("./infor.txt",O_RDWR|O_APPEND,0664))==-1)
		{
			printf("Can not open file to write data\n");
		}

		write (fd2,data->date,real2);

		for(int i = 0;i<length3;i++)
		{	
			if(data->hmtwn[i]!='\0')
			{	
				++real3;
			}
		}

		if((fd3=open("./infor.txt",O_RDWR|O_APPEND,0664))==-1)
		{
			printf("Can not open file to write data\n");
		}
		write (fd3,data->hmtwn,real3);

		
		counter -= 2;

		}
		pthread_mutex_unlock(&lock);
		}

		
}

void static *thr_handle3(void *argvs)
{	
	student *data = (student*) argvs;
	pthread_mutex_lock(&lock);

	while(1)
	{	
		if(counter == -1)
		{
			printf("Student's list after updated: \n");
			system("cat infor.txt");

			printf("Do you want to submit more student's information? [Enter to continue/Enter 'N' or 'n' to stop]\n");
			char buf;
			
			while(1)
			{
				if((buf=getchar())=='\n')
				{
					break;
				}		
				if(buf=='N'||buf=='n')
				{
					exit(0);
				}
			}

			++counter;

		}

	
		pthread_cond_signal(&cond);
		

		pthread_mutex_unlock(&lock);

	}
}
	

int main(int argc,char*argvs[])
{	
	int ret;
	student data = {0};
	
	printf("Program rebooting...\n");
	printf("Waiting for 2s...\n");
	//create thread
	if(ret = pthread_create(&threadid1,NULL,&thr_handle1,&data))
	{
		printf("pthread 1 create error number=%d\n",ret);
		return -1;
	}
	
	sleep(2);

	printf("Waiting for 2s... Please be patient... It's almost done ^-^\n");
	if(ret = pthread_create(&threadid2,NULL,&thr_handle2,&data))
	{
		printf("pthread 2 create error number=%d\n",ret);
		return -1;
	}

	sleep(2);

	printf("Program Start!\n");
	if(ret = pthread_create(&threadid3,NULL,&thr_handle3, &data))
	{
		printf("pthread 3 create error number=%d\n",ret);
		return -1;
	}
	

	pthread_join(threadid1,NULL);
	pthread_join(threadid2,NULL);
	pthread_join(threadid3,NULL);
	return 0;
}
