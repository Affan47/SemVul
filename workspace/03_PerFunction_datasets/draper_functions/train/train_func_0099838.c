ppm_decode_init(ppm_data_t *ppm_data, int fd, unpack_data_t *unpack_data, int *EscChar)
{
	int max_order, Reset, MaxMB;

	max_order = rar_get_char(fd, unpack_data);
	rar_dbgmsg("ppm_decode_init max_order=%d\n", max_order);
	Reset = (max_order & 0x20) ? 1 : 0;
	rar_dbgmsg("ppm_decode_init Reset=%d\n", Reset);
	if (Reset) {
		MaxMB = rar_get_char(fd, unpack_data);
		rar_dbgmsg("ppm_decode_init MaxMB=%d\n", MaxMB);
	} else {
		if (sub_allocator_get_allocated_memory(&ppm_data->sub_alloc) == 0) {
			return FALSE;
		}
	}
	if (max_order & 0x40) {
		*EscChar = rar_get_char(fd, unpack_data);
		rar_dbgmsg("ppm_decode_init EscChar=%d\n", *EscChar);
	}
	range_coder_init_decoder(&ppm_data->coder, fd, unpack_data);
	if (Reset) {
		max_order = (max_order & 0x1f) + 1;
		if (max_order > 16) {
			max_order = 16 + (max_order - 16) * 3;
		}
		if (max_order == 1) {
			sub_allocator_stop_sub_allocator(&ppm_data->sub_alloc);
			return FALSE;
		}
		if(!sub_allocator_start_sub_allocator(&ppm_data->sub_alloc, MaxMB+1)) {
		    sub_allocator_stop_sub_allocator(&ppm_data->sub_alloc);
		    return FALSE;
		}
		if (!start_model_rare(ppm_data, max_order)) {
		    sub_allocator_stop_sub_allocator(&ppm_data->sub_alloc);
		    return FALSE;
		}
	}
	rar_dbgmsg("ppm_decode_init done: %d\n", ppm_data->min_context != NULL);
	return (ppm_data->min_context != NULL);
}
