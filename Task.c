#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define FileName "TaskFile.txt"

int main(){

	pid_t p;
	char buf[100];

	printf("Enter text to be printed to file by parent process:\n");
	scanf("%[^\n]s", buf); 
	int n = (int)strlen(buf);

	int fd;
	mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR | S_IXOTH | S_IXGRP;
  	if ((fd = open(FileName, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, mode))<0){
    	printf("File opening error.\n");
    	close(fd);
  	}
  		p = fork();

	if (p < 0) {
		printf("Fork error.\n");
	} else if (p == 0) {
		//child, read from file and print on terminal
		char val[n];
		if (read(fd, &val, n) != n) {
     		printf("Reading error.\n");
   		} 
   		printf("\nReading from file:\n");
   		printf("%s\n", val);
   		
	} else {
		//parent, write something to file
		//int fd = open("TaskFile.txt", O_CREAT, ... /* mode_t mode */ );
		
		if (lseek(fd, 0, SEEK_END) < 0) {
  			printf("Lseek 1 error.");
  		}

  		if (write(fd, buf, n) != n) {
    		printf("Writing error.\n");
  		} else {
  			printf("Written to file from parent process.\n");
  		}

  		if (lseek(fd, -n, SEEK_END) < 0) {
  			printf("Lseek 2 error.");
  		}
  	}
}