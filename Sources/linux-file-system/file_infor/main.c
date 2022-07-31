/*YEU CAU:
        Tao filesytem.txt va ghi mot doan du lieu bat ki.
        Thuc hien in ra man hinh cac thong tin: Loai file,
        thoi gian chinh sua file lan cuoi, kich thuoc*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h> //this lib contain mode of all func types in sys/stat.h lib
#include <time.h>
#include<stdint.h>
#include<stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	int fd;
	struct stat sb;
	//create file 
	if((fd=open("./filesystem.txt",O_RDWR|O_CREAT,0664))==-1) {
		printf("can not create file\n");
	}
	
	//those if (2 if) to make sure that we just read infor from 1 file only
	if (argc != 2) {
		fprintf(stderr, "Usage: %s ./file-infor/file\n",argv[0]);
		exit(EXIT_FAILURE); // unsucessful execution of a program then quit program
	}

	if (lstat(argv[1],&sb) == -1) {
		perror("lstat");
		exit(EXIT_FAILURE);
	}
	
	//Loai File
	printf("File type:		");
	//sb.stmode AND S_FMT to consider only the bits involved to determine file type
	//S_IFMT is bit mask for file type (S_IFMT is type of file)
	//st_mode contains the file type and permission mode
	// https://man7.org/linux/man-pages/man7/inode.7.html  for more details
	switch(sb.st_mode & S_IFMT) {
	case S_IFBLK:  printf("block device\n"); 	break;
	case S_IFCHR:  printf("character device\n"); 	break;
	case S_IFDIR:  printf("directory\n"); 		break;
	case S_IFIFO:  printf("FIFO/pipe\n"); 		break;
	case S_IFLNK:  printf("symlink\n"); 		break;
	case S_IFREG:  printf("regular file\n"); 	break;
	case S_IFSOCK: printf("socket\n"); 		break;
	default:       printf("unknown?\n");		break;
	}
	
	//Thoi gian thay doi trang thai cuoi cung cua file
	printf("Last status change:	%s",ctime(&sb.st_ctime));
	//Thoi gian file duoc truy cap lan cuoi	
	printf("Last file access:	%s",ctime(&sb.st_atime));
	//Thoi gian chinh sua file lan cuoi
	printf("Last file modification:	%s", ctime(&sb.st_mtime));

	//Kich thuoc file
	printf("File size:	        %jd bytes\n",(intmax_t) sb.st_blksize);
	//intmax_t is the largest int type that your implementation and its standard lib support in conjunction
	exit(EXIT_SUCCESS); //sucessful execution of a program then end program
}

