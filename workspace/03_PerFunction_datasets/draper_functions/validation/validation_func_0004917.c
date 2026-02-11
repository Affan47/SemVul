isl_basic_set_list_underlying_set(
	__isl_take isl_basic_set_list *list)
{
	int i, n;

	if (!list)
		return NULL;

	n = isl_basic_set_list_n_basic_set(list);
	for (i = 0; i < n; ++i) {
		isl_basic_set *bset;

		bset = isl_basic_set_list_get_basic_set(list, i);
		bset = isl_basic_set_underlying_set(bset);
		list = isl_basic_set_list_set_basic_set(list, i, bset);
	}

	return list;
}
