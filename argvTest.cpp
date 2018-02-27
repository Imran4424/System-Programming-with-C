/*
In this program we are trying to pass arguments through command line

*/


#include <stdio.h>


int main(int ar_numbers,char *argv[])
{
	printf("Number of parameters: %d\n",ar_numbers);
	
	printf("%s %s %s %s\n",argv[0],argv[1],argv[2],argv[3]);


	return 0;
}
