static void prio_add(priority_st * priority_list, unsigned int algo)
{
	unsigned int i, l = priority_list->algorithms;

	if (l >= MAX_ALGOS)
		return;

	for (i = 0; i < l; ++i) {
		if (algo == priority_list->priority[i])
			return;
	}

	priority_list->priority[l] = algo;
	priority_list->algorithms++;

	return;
}
