rar_init_filters(unpack_data_t *unpack_data)
{
	if (unpack_data->old_filter_lengths) {
		free(unpack_data->old_filter_lengths);
		unpack_data->old_filter_lengths = NULL;
	}
	unpack_data->old_filter_lengths_size = 0;
	unpack_data->last_filter = 0;

	rar_filter_array_reset(&unpack_data->Filters);
	rar_filter_array_reset(&unpack_data->PrgStack);
}
