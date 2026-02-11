_sort_by_max_time(void *void1, void *void2)
{
	int diff;
	sinfo_data_t *sinfo1;
	sinfo_data_t *sinfo2;
	uint32_t val1 = 0, val2 = 0;

	_get_sinfo_from_void(&sinfo1, &sinfo2, void1, void2);

	if (sinfo1->part_info)
		val1 = sinfo1->part_info->max_time;
	if (sinfo2->part_info)
		val2 = sinfo2->part_info->max_time;
	diff = val1 - val2;

	if (reverse_order)
		diff = -diff;
	return diff;
}
