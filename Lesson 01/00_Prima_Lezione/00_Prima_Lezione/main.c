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
	printf("MCD= %d\n", res);

	res = euclide_iter(x, y);

	printf("MCD= %d\n", res);
}

int euclide(int x, int y)
{
	int resto;

	if (y == 0)
		return x;
	else
	{
		//l'operazione può essere anche inserita all'interno della ricorsione senza dover usare variabili aggiuntive, ottimizzando il codice
		resto = x % y;
		x = y;
		y = resto;

		return euclide(x, y);
	}
}

int euclide_iter(int x, int y)
{
	//qui invece la variabile temporanea è obbligatoria altimenti non si riesce a salvare il resto
	int resto;

	while (y != 0)
	{
		resto = x % y;
		x = y;
		y = resto;

	}

	return x;
}
