#include <stdio.h>  

void main(int argc, char* argv[])
{
	int x, y, res;
	if (argc != 3)
	{
		printf("Errore: numero di parametri errato");
		return;
	}
	
	x = atoi(argv[1]);
	y = atoi(argv[2]);

	if (x < 0 || y < 0)
	{
		printf("Errore: x e y devono essere due numeri naturali (>=0)");
		return;
	}

	if (x < y)
	{
		printf("Errore: x deve essere maggiore o uguale a y");
		return;
	}

	res = euclide(x, y);
	//res = euclide_iter(x, y);
	
	printf("MCD= %d\n", res);
}

int euclide(int x, int y)
{
	//TODO
}

int euclide_iter(int x, int y)
{
	//TODO
}
