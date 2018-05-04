/*this code demostrate the zoombie process

zoombie process is a child process

	which is dead but it's information is still in system

In termial,

	To compile:  gcc zoombie_process.c -o zoombie_process

	To run:      ./zoombie_process
---------------------------------------------------------
Necessary System calls:
						fork()
						exit(0)
---------------------------------------------------------
---------------------------------------------------------

*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	pid_t childPID;

	childPID = fork();

	if(childPID < 0)
	{
		printf("child Process creation failed\n");
	}
	else if(childPID == 0)
	{

		printf("I am child Process.My pid is: %d\n", getpid());

		exit(0);

	}
	else
	{
		//sleep(10);


		printf("I am parent process.my pid: %d\n", getpid());
		printf("My child process is: %d\n",childPID);

		while(1);
	}

	//return 0;
}