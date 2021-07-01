
//Combina i due sottoarray ordinati [p, q] e [q+1, r].
//La implementazione è non in place poichè ci dobbiamo appoggiare ad un secondo array e non riusciamo a lavorare solo su
//quello che passiamo come argomento
void merge(int *array, int p, int q, int r)
{
	int i = p, j = q + 1, k = 0;
	int *array2;

	array2 = (int *)malloc((r - p + 1) * sizeof(int));

	while (i <= q && j <= r)
	{
		if (array[i] < array[j])
			array2[k] = array[i++];
		else
			array2[k] = array[j++];

		k++;
	}
	
	while (i <= q)
		array2[k++] = array[i++];
	
	while (j <= r)
		array2[k++] = array[j++];

	for (k = p; k <= r; k++)
	{
		array[k] = array2[k - p];
	}

	free(array2);
}

// Ordina l'array dall'indice p all'indice r inclusi
void mergeSort(int *data, int p, int r)
{
	int q = (p + r) / 2;				// si noti che in C la divisione tra interi memorizzata in variabile intera comporta il troncamento del numero all'intero inferiore (floor)
	if (p < r)
	{
		mergeSort(data, p, q);			// Ordina il sottoarray di sinistra
		mergeSort(data, q + 1, r);		// Ordina il sottoarray di destra
		merge(data, p, q, r);			// Combina i due sottoarray
	}
}