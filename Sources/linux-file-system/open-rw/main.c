//C program to il1lustrate
// I/O system Calls
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(void)
{
	int fd;
	int numb_read, numb_write;
	char buf1[12] = "hello world\n";
	//assume foobar.txt is always created
	umask(0000);
	fd = open("hello.txt", O_RDWR|O_CREAT,0667);
	if(fd == -1) {
		printf("open() hello.txt failed\n");
	}
	
	numb_write = write(fd,buf1,strlen(buf1));
	printf("Write %d bytes to hello.txt\n", numb_write);
	
	lseek(fd,2,SEEK_SET);
	write(fd,"HOADEV",strlen("HOADEV"));

	close(fd);

	return 0;
}
