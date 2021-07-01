
int partition(int *array, int p, int r)
{
	int i = p - 1, x = array[r];
	int t;

	for (int j = p; j <= (r - 1); j++)
	{
		if (array[j] <= x)
		{
			i++;
			t = array[i];
			array[i] = array[j];
			array[j] = t;
		}

		t = array[i + 1];
		array[i + 1] = array[r];
		array[r] = t;

		return i + 1;
	}
}

void quicksort(int *data, int p, int r)
{
	int q;
	if (p < r)
	{
		q = partition(data, p, r);
		quicksort(data, p, q - 1);
		quicksort(data, q + 1, r);
	}
}