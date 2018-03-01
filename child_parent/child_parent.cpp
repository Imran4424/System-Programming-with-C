/*
	Here we implement a code to create child proecess

	here we create 5 child process from a single parent

	here "fork()" function is called to create the child process

	after calling fork(),

						it will return the child proceess id to the parent process

						it will return 0 to the child process

	we use "getpid()" function to achieve current process id, for both parent and child process


	we use one more function for child process
	that is "getppid()"
	to achieve parent process id for this child

*/

#include<stdio.h>
#include<unistd.h>      // For getpid(), getppid(), fork()
#include<sys/wait.h>
#include <iostream>
using namespace std;

pid_t myPID;


int main()
{
	pid_t childPID;

	childPID = fork();
	myPID = getpid();
	
	if (childPID < 0)
	{
		printf("fork failed \n");
	}
	else if(childPID == 0 )
	{
		printf("#######I am child One - %d,My parent is  %d \n\n",myPID,getppid());
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
			printf("#######I am child two - %d,My parent is  %d \n\n", myPID,getppid());
		}
		else
		{

			pid_t childPID3;

			childPID3 = fork();
			myPID = getpid();
	
			if (childPID3 < 0)
			{
				printf("fork failed \n");
			}
			else if(childPID3 == 0 )
			{
				printf("#######I am child three- %d,My parent is  %d \n\n",myPID,getppid());
			}
			else
			{


				pid_t childPID4;

				childPID4 = fork();
				myPID = getpid();
	
				if (childPID4 < 0)
				{
					printf("fork failed \n");
				}
				else if(childPID4 == 0 )
				{
					printf("#######I am child four- %d,My parent is  %d \n\n", myPID, getppid());
				}
				else
				{

					pid_t childPID5;

					childPID5 = fork();
					myPID = getpid();
	
					if (childPID5 < 0)
					{
						printf("fork failed \n");
					}
					else if(childPID5 == 0 )
					{
						printf("#######I am child five- %d,My parent is  %d \n\n", myPID,getppid());
					}
					else
					{


				
						printf("\nI am parent of child %d, My PID is %d .\n\n", childPID5, myPID);
						wait(NULL);
						printf("My child is really dead. %d\n\n",childPID5);
					}


				
					printf("\nI am parent of child %d, My PID is %d .\n\n", childPID4, myPID);
					wait(NULL);
					printf("My child is really dead. %d\n\n",childPID4);
				}

				
				printf("\nI am parent of child %d, My PID is %d .\n\n", childPID3, myPID);
				wait(NULL);
				printf("My child is really dead. %d\n\n",childPID3);
			}



			printf("\nI am parent of child %d, My PID is %d .\n\n", childPID2, myPID);
			wait(NULL);
			printf("My child is really dead. %d\n\n",childPID2);
		}


		printf("\nI am parent of child %d, My PID is %d .\n\n", childPID, myPID);
		wait(NULL);
		printf("My child is really dead. %d\n\n",childPID);
	}


	while(1); //infinity loop to hold the program to view pstree -p

	return 0;
}
