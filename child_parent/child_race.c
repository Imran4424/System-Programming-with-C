/*in this code we will understand the nature of

		multiple child process

		they are : child processes run independently

				   child process run concurrently

		this is described by creating a child race between two child processes

in terminal,

	to compile: gcc child_race.c -o child_race
	to run:     ./child_race

*/


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


pid_t myPID;

#define N 200
#define MSG_SZ 200

int a; //global variable;

void child_one()
{
	int i;
	char msg[MSG_SZ];	

	for (i = 1; i <= N; i++) {
		
		sprintf(msg, "%d. I am Child One. My task is to increase a. Before (a = a + 1): %d\n", i, a);	
		write(1, msg, strlen(msg) + 1);
		a = a + 1;
		sprintf(msg, "%d. I am Child One. My task is to increase a. After (a = a + 1): %d\n", i, a);
		write(1, msg, strlen(msg) + 1);
	}	

}

void child_two()
{
	int i;
	char msg[MSG_SZ];	

	for (i = 1; i <= N; i++) {
		sprintf(msg, "%d. I am Child two. My task is to decrease a. Before (a = a - 1): %d\n", i, a);	
		write(1, msg, strlen(msg) + 1);
		a = a - 1;
		sprintf(msg, "%d. I am Child two. My task is to decrease a. After (a = a - 1): %d\n", i, a);
		write(1, msg, strlen(msg) + 1);
	}	


}

int main()
{
	a = 0; 

	int second_child;

	pid_t childPID;

	childPID = fork();
	myPID = getpid();
	
	
	if (childPID < 0)
	{
		printf("fork failed \n");
	}
	else if(childPID == 0 )
	{
		printf("#######I am child One %d\n",myPID);
		
		child_one();
	}
	else
	{
		pid_t childPID2;

		childPID2 = fork();
		myPID = getpid();
	
		if (childPID2 < 0)
		{
			printf("fork failed \n");
		}
		else if(childPID2 == 0 )
		{
			printf("#######I am child two - %d",  myPID);
			
			child_two();
		}
	
	}
	
	
	

	return 0;
}
