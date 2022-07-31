#include<stdio.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	char text[12] = {0};
	struct flock fl;

	sprintf(text,"hello world"); 

	if((fd=open("./test.txt", O_RDWR | O_CREAT,0666)) == -1) {
		printf("can not create file \n");
		return 0;
	} else {
		printf("create file test.txt\n");
	}

	if(write(fd,text, sizeof(text) - 1) == -1) {
		printf("can not write file \n");
		return 0;
	} else {
		printf("write file \n");
	}

	fl.l_start  = 1;
	fl.l_len = 5;
	fl.l_type = F_WRLCK;
	fl.l_whence = SEEK_SET;
	
	if(fcntl(fd,F_SETLK,&fl) == -1) {
		printf("can not set write lock byte 1-5\n");
	} else {
		printf("set write lock byte 1-5 \n");
	} 
	
	while(1) {
		sleep(1);
	}

	close(fd);
	return 0;
}
