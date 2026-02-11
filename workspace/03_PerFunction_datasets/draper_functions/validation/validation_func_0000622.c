get_free_data_block() {
	int i, result;
	int block_index;

	result = 0;


	for (i = 0; i < data_block_size; i++) {
		if (super->block_freelist[i] == 0) {
			block_index = i;
			super->block_freelist[i] = OCCUPIED;
			result = 1;
			break;
		}
	}

	if (result == 1) {
		write_super_blocks();
		return block_index + DATA_OFFSET;
	} else
		return -1;
}
