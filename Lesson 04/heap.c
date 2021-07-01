#include <stdio.h>
#include <math.h>

// Preserva la proprietà fondamentale del MaxHeap
void maxHeapify(int* data, int n, int i)
{
	int l, r, largest, temp;
	l = (2 * i) + 1;
	r = l + 1;
	if (l <= (n - 1) && data[l] > data[i])
		largest = l;
	else
		largest = i;
	if (r <= (n - 1) && data[r] > data[largest])
		largest = r;
	if (largest != i)
	{
		temp = data[i];
		data[i] = data[largest];
		data[largest] = temp;
		maxHeapify(data, n, largest);
	}
}

void buildMaxHeap(int* data, int n)
{
	int i;
	for (i = ((int)n / 2) - 1; i >= 0; i--)
		maxHeapify(data, n, i);
}

// Funzione di stampa
void printHeap(int* data, int n)
{
	int i, j;
	int line = 1;
	//altezza dello heap
	int h = ((int)log2(n)) + 1;
	//step di riga iniziale, da stampare prima della radice
	int step = ((int)pow(2, h - line)) - 1;
	printf("\n");
	for (j = 0; j < step; j++)
		printf("\t");
	for (i = 0; i < n; i++)
	{
		if (((int)log2(i + 1)) > line - 1)
		{
			line++;
			step = ((int)pow(2, h - line)) - 1;
			printf("\n\n");
			//step al cambio riga
			for (j = 0; j < step; j++)
				printf("\t");
		}

		printf("%d", data[i]);
		//step intermedio, da stampare tra un elemento e l'altro della stessa riga
		for (j = 0; j < (2 * step) + 2; j++)
			printf("\t");

	}
	printf("\n\n");
}