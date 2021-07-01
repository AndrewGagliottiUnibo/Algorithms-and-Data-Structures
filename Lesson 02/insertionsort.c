void insertionSort(int *data, int n)
{
	int key, i;

	for (int j = 1; j < n; j++)
	{
		key = data[j];
		i = j - 1;

		while (i > - 1 && data[i] > key)
		{
			data[i + 1] = data[i];
			i = i - 1;
		}

		data[i + 1] = key;
	}
}