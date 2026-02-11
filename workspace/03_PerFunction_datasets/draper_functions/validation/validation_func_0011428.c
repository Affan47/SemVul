write_sparse_fill_chunk(struct output_file *out, unsigned int len,
		uint32_t fill_val)
{
	chunk_header_t chunk_header;
	int rnd_up_len, zero_len, count;
	int ret;
	unsigned int i;


	rnd_up_len = ALIGN(len, out->block_size);


	chunk_header.chunk_type = CHUNK_TYPE_FILL;
	chunk_header.reserved1 = 0;
	chunk_header.chunk_sz = rnd_up_len / out->block_size;
	chunk_header.total_sz = CHUNK_HEADER_LEN + sizeof(fill_val);
	ret = out->ops->write(out, &chunk_header, sizeof(chunk_header));

	if (ret < 0)
		return -1;
	ret = out->ops->write(out, &fill_val, sizeof(fill_val));
	if (ret < 0)
		return -1;

	if (out->use_crc) {
		count = out->block_size / sizeof(uint32_t);
		while (count--)
			out->crc32 = sparse_crc32(out->crc32, &fill_val, sizeof(uint32_t));
	}

	out->cur_out_ptr += rnd_up_len;
	out->chunk_cnt++;

	return 0;
}
