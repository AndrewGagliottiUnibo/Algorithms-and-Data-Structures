
void buildMaxHeap(int *data, int n);
void maxHeapify(int *data, int n, int i);

// Ordina gli elementi dello heap
void heapsort(int *data, int n)
{
	int t;

	buildMaxHeap(data, n);
	while (n > 0)
	{
		t = data[0];
		data[0] = data[n - 1];
		data[n - 1] = t;
		n--;
		maxHeapify(data, n, 0);
	}
}