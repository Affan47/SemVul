ReadData(void *ret_data, int in_max, int *ret_len) {
	if (read_buf == NULL)
		return 0;

    read_buf->FetchPtr((uint8_t *) ret_data, in_max, ret_len);

    return (*ret_len);
}
