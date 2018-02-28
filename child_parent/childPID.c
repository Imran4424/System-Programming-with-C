#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	//int i;
	pid_t childPID, myPID;
	
	/*
	   0 > childPID --> unsuccessful
	   0 = childPID --> child process
	   0 < childPID --> parent process 
	*/
	
	childPID = fork();
	myPID = getpid();
	
	if (childPID < 0)
	{
		printf("fork failed \n");
	}
	else if(childPID == 0 )
	{
		printf("I am child - %d,My parent is  %d \n\n", childPID, myPID);
	}
	else
	{
		printf("\nI am parent of child %d, My PID is %d .\n\n", childPID, myPID);
		wait(NULL);
		printf("My child is really dead.\n\n");
	}

	return 0;
}
