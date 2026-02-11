ang_sort_comp_hook(const void *u, const void *v, int a, int b)
{
	const u16b *who = (const u16b *)(u);
	const u16b *why = (const u16b *)(v);

	int w1 = who[a];
	int w2 = who[b];

	int z1, z2;


	if (*why >= 4)
	{

		z1 = l_list[w1].pkills;
		z2 = l_list[w2].pkills;


		if (z1 < z2) return (TRUE);
		if (z1 > z2) return (FALSE);
	}


	if (*why >= 3)
	{

		z1 = l_list[w1].tkills;
		z2 = l_list[w2].tkills;


		if (z1 < z2) return (TRUE);
		if (z1 > z2) return (FALSE);
	}


	if (*why >= 2)
	{

		z1 = r_info[w1].level;
		z2 = r_info[w2].level;


		if (z1 < z2) return (TRUE);
		if (z1 > z2) return (FALSE);
	}


	if (*why >= 1)
	{

		z1 = r_info[w1].mexp;
		z2 = r_info[w2].mexp;


		if (z1 < z2) return (TRUE);
		if (z1 > z2) return (FALSE);
	}


	return (w1 <= w2);
}
