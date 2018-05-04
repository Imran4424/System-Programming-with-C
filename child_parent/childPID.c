/*
===================================================================================================
	Here we implement a code to create child proecess

	here we create a single child process

	here "fork()" function is called to create the child process

	after calling fork(),

						it will return the child proceess id to the parent process

						it will return 0 to the child process

	we use "getpid()" function to achieve current process id, for both parent and child process


	we use one more function for child process
	that is "getppid()"
	to achieve parent process id for this child

---------------------------------------------------------
Necessary System calls:
						fork()
						getpid()
						getppid()
---------------------------------------------------------
SHAH MD. IMRAN HOSSAIN
    Dept. of CSE, University of Rajshahi,
    Rajshahi-6205, Bangladesh
---------------------------------------------------------

===================================================================================================
*/


#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	//int i;
	pid_t childPID, myPID, parent_pid;

	char message[100];
	
	/*
	   0 > childPID --> unsuccessful
	   0 = childPID --> child process
	   0 < childPID --> parent process 
	*/
	
	childPID = fork();
	myPID = getpid();

	

	//sleep(1);
	
	if (childPID < 0)
	{
		printf("fork failed \n");
	}
	else if(childPID == 0 )
	{
		parent_pid = getppid();

		printf("I am child - %d,My Parent is %d \n\n",myPID,parent_pid);
	}
	else
	{
		printf("\nI am parent of child %d, My PID is %d .\n\n", childPID, myPID);


		wait(NULL);     //here wait function return the pid of dead child

		printf("My child is really dead.\n\n");
	}

	return 0;
}
