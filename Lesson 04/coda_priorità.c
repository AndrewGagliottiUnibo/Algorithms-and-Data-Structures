
void maxHeapify(int *data,int n, int i);

// Restituisce il massimo elemento presente nel MaxHeap
// Lo rimuove e richiama maxHeapify per ripristinare la proprietà fondamentale
int extractMax(int *data, int *n)
{
	int max;
	
	max = data[0];
	data[0] = data[(*n) - 1];
	(*n)--;
	maxHeapify(data, *n, 0);

	return max;
}