/*
======================================================================
This is a code to demonstrate Orphan child state


Orphan child is a child process running
					whose parent is dead.


to compile this code on linux, in terminal

	gcc orphan_child.c -o orphan_child

to run just type

		./orphan_child
---------------------------------------------------------
Necessary System calls:
						fork()
						getpid()
---------------------------------------------------------
SHAH MD. IMRAN HOSSAIN
    Dept. of CSE, University of Rajshahi,
    Rajshahi-6205, Bangladesh
---------------------------------------------------------
======================================================================
*/

#include <stdio.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
	pid_t childPID;

	childPID = fork();

	if(childPID < 0)
	{
		printf("child create failed\n");
	}
	else if(childPID == 0)
	{
		while(1)
		{

			printf("I am child process.My pid is %d\n",getpid());
		}


		
	}
	else
	{
		printf("I am parent process.My pid is %d\n",getpid());

		//return 0;
	}


	return 0;
}