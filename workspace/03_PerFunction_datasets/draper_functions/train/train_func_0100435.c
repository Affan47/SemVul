writer_write(struct writer *writer, struct iovec *iov, int iov_cnt,
		 uint64_t *offset_ptr)
{
	uint64_t prev_size = writer->file_size;
	int r = file_appendv(writer->file, iov, iov_cnt, prev_size);
	if (r == -1) {
		return -1;
	}
	writer->file_size += r;
	*offset_ptr = prev_size;
	return r;
}
