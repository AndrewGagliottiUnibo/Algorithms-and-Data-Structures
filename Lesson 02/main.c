#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LINE_LENGTH 120
#define PRINT_OUTPUT 1

void insertionSort(int* data, int n);
void mergeSort(int* data, int p, int r);
void quicksort(int* data, int p, int r);

// Main
//argv[1] = nome del file da caricare
void main(int argc, char* argv[])
{
	char line[LINE_LENGTH];
	int i, n, *arr;
	clock_t start, end;

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

	//Ordinamento
	printf("Ordinamento ...\n");
	start = clock();
	insertionSort(arr, n);
	//mergeSort(arr, 0, n-1);
	//quicksort(arr, 0, n - 1);
	end = clock();
	//---

	if (PRINT_OUTPUT)
	{
		printf("Dopo l'ordinamento:\n");
		for (i = 0; i < n; i++)
			printf("%d\n", arr[i]);
	}
	
	free(arr);

	printf("Tempo di esecuzione: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC);
}