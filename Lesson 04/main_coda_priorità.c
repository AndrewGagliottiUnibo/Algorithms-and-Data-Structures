#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH 120
#define PRINT_OUTPUT 1

void buildMaxHeap(int *data, int n);
int extractMax(int *data, int *n);

//Main
//argv[1] = percorso del file contenente un elenco di numeri interi
void main(int argc, char* argv[])
{
	char line[LINE_LENGTH];
	int i, n, *arr;

	if (argc != 2)
	{
		printf("Errore: numero di parametri errato");
		return;
	}

	//Lettura da file dell'array non ordinato
	printf("Lettura del file %s\n", argv[1]);
	FILE* fin = fopen(argv[1], "r");
	if (fin == NULL)
		return;

	n = 0;
	while (fgets(line, LINE_LENGTH, fin) != NULL) n++;
	arr = (int*)calloc(n, sizeof(int));
	rewind(fin);
	n = 0;
	while (fgets(line, LINE_LENGTH, fin) != NULL)
	{
		arr[n] = atoi(line);
		if (PRINT_OUTPUT)
			printf("%d\n", arr[n]);
		n++;
	}
	fclose(fin);
	printf("\n");
	//---

	//Costruzione MaxHeap
	printf("Costruzione dello heap...\n");
	buildMaxHeap(arr, n);
	//---

	//Coda a priorità
	printf("Estrazione degli elementi da coda con priorita':\n");
	while (n > 0)
	{
		i = extractMax(arr,&n);
		if (PRINT_OUTPUT)
			printf("Elemento estratto: %d\n", i);
	}

	free(arr);
}