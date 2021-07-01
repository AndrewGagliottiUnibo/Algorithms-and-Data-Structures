#include <stdio.h>

void passByVal(int number)
{
	number *= 2;
	printf("Pass by val:, number = %d\n", number);
}

void passByRef(int* pNumber)
{
	*pNumber *= 2;
	printf("Pass by ref:, *pNumber = %d\n", *pNumber);
}

void main()
{
	int number = 20;
	printf("number = %d\n", number);
	passByVal(number);
	printf("number = %d\n", number);
	passByRef(&number);
	printf("number = %d\n", number);
}