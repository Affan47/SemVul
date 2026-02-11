read_blockwise(int fd, void *orig_buf, size_t count) {
	void *hangover_buf, *hangover_buf_base;
	void *buf, *buf_base = NULL;
	int r, hangover, solid, bsize, alignment;
	ssize_t ret = -1;

	if ((bsize = sector_size(fd)) < 0)
		return bsize;

	hangover = count % bsize;
	solid = count - hangover;
	alignment = get_alignment(fd);

	if ((long)orig_buf & (alignment - 1)) {
		buf = aligned_malloc(&buf_base, count, alignment);
		if (!buf)
			goto out;
	} else
		buf = orig_buf;

	r = read(fd, buf, solid);
	if(r < 0 || r != solid)
		goto out;

	if (hangover) {
		hangover_buf = aligned_malloc(&hangover_buf_base, bsize, alignment);
		if (!hangover_buf)
			goto out;
		r = read(fd, hangover_buf, bsize);
		if (r <  0 || r != bsize)
			goto out;

		memcpy(buf + solid, hangover_buf, hangover);
		free(hangover_buf_base);
	}
	ret = count;
 out:
	if (buf != orig_buf) {
		memcpy(orig_buf, buf, count);
		free(buf_base);
	}
	return ret;
}
