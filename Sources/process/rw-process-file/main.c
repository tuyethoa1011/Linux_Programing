/* Viet mot chuong trinh A tao ra mot tien trinh con
B. Ben trong A thuc hien tao ra file hello.txt nam o duong dan ./log/hello.txt
va ghi thong diep vao file day. O B se thuc hien doc lai noi dung file va in ra man hinh.*/

//Tom tat yeu cau: - Tao tien trinh con , tien trinh cha
//		   - Tien trinh cha thuc hien tao ra file hello.txt theo path, ghi thong diep vao file day
//		   - Tien trinh con doc lai noi dung file va in ra man hinh

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	int fd1,fd2;	
	char buf1[17] = {0};

	sprintf(buf1,"Xin chao cac ban!");

	pid = fork(); // Create child process
	
	if(pid >=0){
		if(pid == 0){ // Child process 
			//open file
			printf("\n--------------CHILD PROCESS--------------\n");
			if((fd2=open("./log/hello.txt", O_RDWR,0664))==-1) { //Luu y: Phai co folder log tao truoc
                                printf("\nOpen file unsuccessfully\n");

                        } else {
                                printf("\nOpen file ./log/hello.txt\n");
                        }
			//read file
                        if((read(fd2,buf1,sizeof(buf1))) == -1) {
                                printf("Read file unsuccessfully! Can't print file's content on screen\n");
                       
                        } else {
				//print file's content
                                printf("hello.txt file's content:\n");
                                printf("%s\n", buf1);
                        }
			printf("\n-----------------------------------------\n");
	
		} else { //Father process
			printf("-------------FATHER PROCESS--------------\n");
			//create file
                        if((fd1=open("./log/hello.txt", O_RDWR | O_CREAT, 0664))==-1) {
                                printf("\nCreate file unsuccessfully\n");

                      	} else {
				printf("\nCreate file ./log/hello.txt\n");
			}
			//write file
                        if((write(fd1,buf1,sizeof(buf1))) == -1) {
                                printf("Write file unsuccessfully\n");
                        } else {
				printf("Write file hello.txt\n");

			}
			while(1);
		
		}
	} else {
		printf("ERROR! Failed to create child process\n");
	}
	close(fd1);
	close(fd2);

	return 0;
}
