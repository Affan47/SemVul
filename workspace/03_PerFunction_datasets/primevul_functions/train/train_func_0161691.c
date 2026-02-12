static void bond_skip_slave(struct bond_up_slave *slaves,
			    struct slave *skipslave)
{
	int idx;


	for (idx = 0; slaves && idx < slaves->count; idx++) {
		if (skipslave == slaves->arr[idx]) {
			slaves->arr[idx] =
				slaves->arr[slaves->count - 1];
			slaves->count--;
			break;
		}
	}
}
