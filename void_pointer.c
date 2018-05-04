/*
	implementing basic concept of void pointer

----------------------------------------------------------------------
    SHAH MD. IMRAN HOSSAIN
    Dept. of CSE, University of Rajshahi,
    Rajshahi-6205, Bangladesh
----------------------------------------------------------------------

*/


#include <stdio.h>

void add(void *x,void *y)
{
	float sum = *(float*) x + *(float*) y;
	
	printf("%f\n",sum);
}



int main()
{
	float x=5,y=10;
	
	add(&x, &y);


	return 0;
}
