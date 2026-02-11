build_heap(int *arr, int size)
{
	int k = 0;
	for (k = size/2; k >=0; k--)
	{
		adjust_heap(arr, k, size);
	}
	return 0;
}
