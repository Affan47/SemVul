write_normal(git_filebuf *file, const void *source, size_t len)
{
	int result = 0;

	if (len > 0) {
		result = p_write(file->fd, (void *)source, len);
		if (file->digest)
			git_hash_update(file->digest, source, len);
	}

	return result;
}
