#include <stdio.h>  
#include <time.h>

void main(int argc, char* argv[])
{
	int a, b, sum = 0;
	clock_t start, end;

	if (argc != 3)
	{
		printf("Numero di parametri errato");
		return;
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);
	printf("Primo parametro = %d\nSecondo parametro = %d\n", a, b);

	start = clock();
	for (int i = 0; i < 1000000; i++)
		sum += a * b;

	end = clock();

	printf("Time: %f sec \n", (double)(end - start) / CLOCKS_PER_SEC);
}