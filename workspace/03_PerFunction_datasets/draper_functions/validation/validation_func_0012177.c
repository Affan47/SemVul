rev_comp_mer(mer_t mer)
{
	mer_t new_mer = 0;
	int i;
	for (i = 0; i < k; i++)
	{


		new_mer = new_mer << 2;
		new_mer = new_mer | (mer & 3);
		mer = mer >> 2;
	}

	return (~new_mer) & k_mask;
}
