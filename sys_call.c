/*
	here we implement two basic system calls 

	"perror" and "open"

*/


#include <stdio.h>          //for perror
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
	int fd;
	
	fd = open("file1.txt", O_RDONLY);
	
	if(fd == -1)
	{
		int errNO = errno;
	
		perror("Error During open()");
		printf("\n\nError NO %d\n",errNO);
		return 1;

	}
	else
	{
		printf("No Error\n");
	}


	return 0;
}
