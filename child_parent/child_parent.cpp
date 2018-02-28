#include<stdio.h>
#include<unistd.h>
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
		printf("#######I am child One - %d,My parent is  %d \n\n", childPID, myPID);
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
			printf("#######I am child two - %d,My parent is  %d \n\n", childPID2, myPID);
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
				printf("#######I am child three- %d,My parent is  %d \n\n", childPID3, myPID);
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
					printf("#######I am child four- %d,My parent is  %d \n\n", childPID4, myPID);
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
						printf("#######I am child five- %d,My parent is  %d \n\n", childPID5, myPID);
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


	while(1)
	{
		cout<<"loop"<<endl;
	}	

	return 0;
}
