/*Viet mot chuong trinh thuc hien tao 2 threads. Ca hai
threads nay deu dung chung mot ham handle. Kiem tra neu
la thread1 dang thuc hien thi in ra thong diep bat ki de
thong bao. Neu la threads thi truyen vao du lieu kieu struct human
duoc khoi tao tu truoc, voi cac thong tin: Ho ten, nam sinh,
sdt, que quan.*/

#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>

pthread_t thread_id1, thread_id2;

typedef struct {
	char name[70]; //hoten
	int year; //namsinh
	char phonenum[20]; //sdt
	char hometwn[50];  //que quan                               
} human;

static void *thr_handle(void *args)
{
	pthread_t tid = pthread_self();
	human *data  = (human*) args;

	if(pthread_equal(tid,thread_id1)){
		printf("I'm thread_id1\n\n");
	} else {
		printf("I'm thread_id2\n");
		printf(">>> HUMAN INFORMATION'S DETECTED\n");
		printf("Name: %s\n",data->name);
		printf("Year born: %d\n",data->year);
		printf("Phone number: %s\n",data->phonenum);
		printf("Hometown: %s\n",data->hometwn);
	}
}



int main()
{	
	int ret;
	human data = {0};
	
	strncpy(data.name,"Ngo Le Tuyet Hoa",sizeof(data.name));
	data.year = 2002;
	strncpy(data.phonenum,"093619247916",sizeof(data.phonenum));
	strncpy(data.hometwn,"Long An",sizeof(data.hometwn));

	if(ret = pthread_create(&thread_id1,NULL,&thr_handle,NULL))
	{
		printf("pthread_create() error number = %d\n",ret);
		return -1;
	}
	
	sleep(2);

	if(ret = pthread_create(&thread_id2,NULL,&thr_handle,&data))
	{
		printf("pthread_create() error number = %d\n",ret);
		return -1;
	}	
	
	sleep(5);

	return 0;
}
