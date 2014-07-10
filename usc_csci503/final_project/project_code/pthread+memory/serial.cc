#include <stdlib.h>
#include <iostream>
#include <stdio.h>

using namespace std;

extern int random(int start, int end);
extern void exchange(double * a, double * b);

int partition(double * A, int p, int r)
{
	int i=random(p, r);
	exchange(A+i, A+r);	

	int x=A[r];
	
	i=p-1;
	for(int j=p;j<r;j++)
	{
		if(A[j]<=x)
		{
			i++;
			exchange(A+i, A+j);
		}
	}
	exchange(A+i+1, A+r);
	
	return i+1;
}

void quicksort(double * A, int p, int r)
{
	if(p<r)
	{
		int q= partition(A, p, r);
		quicksort(A, p, q-1);
		quicksort(A, q+1, r);
	
	}

}


void serial_main(int arraySize, double * array)
{
	quicksort(array, 0, arraySize-1);

}
