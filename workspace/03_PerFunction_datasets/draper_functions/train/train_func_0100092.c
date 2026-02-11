_print_priority(sinfo_data_t * sinfo_data, int width,
			bool right_justify, char *suffix)
{
	char id[FORMAT_STRING_SIZE];

	if (sinfo_data) {
		_build_min_max_16_string(id, FORMAT_STRING_SIZE,
				      sinfo_data->part_info->priority,
				      sinfo_data->part_info->priority, true);
		_print_str(id, width, right_justify, true);
	} else
		_print_str("PRIORITY", width, right_justify, true);

	if (suffix)
		printf("%s", suffix);
	return SLURM_SUCCESS;
}
