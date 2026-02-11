comb_sort(data array[], int len) {
	int gap = len;
	int swaps = 0;
	int i;
	data tmp;
	while (gap > 1 || swaps) {
		if (gap > 1)
			gap /= 1.247330950103979;
		swaps = 0;
		for (i = 0; i+gap < len; i++)
			if (array[i] > array[i+gap]) {
				tmp = array[i];
				array[i] = array[i+gap];
				array[i+gap] = tmp;
				swaps = 1;
			}
	}
}
