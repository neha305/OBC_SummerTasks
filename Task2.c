#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define FileName "Task2File.txt"
#define max_size 100

int main(){

	pid_t p;
	char buf[100];

	int fd;
	int n;
	mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR | S_IXOTH | S_IXGRP;
  	if ((fd = open(FileName, O_RDWR | O_CREAT | O_TRUNC | O_APPEND, mode))<0){
    	printf("File opening error.\n");
    	close(fd);
  	}
  		p = fork();

	if (p < 0) {
		printf("Fork error.\n");
	} else if (p == 0) {
		//child
		printf("p : %d\n", p);
		printf("Enter text to be printed to file by child process:\n");
		fgets(buf, sizeof(buf), stdin); 
		n = (int)strlen(buf);

  		if (write(fd, buf, n) != n) {
    		printf("Writing error.\n");
  		} else {
  			printf("Written to file from child process.\n");
  		}
   		
	} else {
		//parent
		sleep(2);
		printf("p : %d\n", p);
		printf("Enter text to be printed to file by parent process:\n");
		fgets(buf, sizeof(buf), stdin);
		n = (int)strlen(buf);

  		if (write(fd, buf, n) != n) {
    		printf("Writing error.\n");
  		} else {
  			printf("Written to file from parent process.\n");
  		}
  	}
}