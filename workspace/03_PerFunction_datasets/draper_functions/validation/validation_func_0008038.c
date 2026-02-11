source_resize(git_odb_source *src)
{
	size_t write_offset, new_size;
	void *new_data;

	write_offset = (size_t)((char *)src->write_ptr - (char *)src->raw.data);

	new_size = src->raw.len * 2;
	if ((new_data = git__malloc(new_size)) == NULL)
		return GIT_ENOMEM;

	memcpy(new_data, src->raw.data, src->written_bytes);
	free(src->raw.data);

	src->raw.data = new_data;
	src->raw.len = new_size;
	src->write_ptr = (char *)new_data + write_offset;

	return GIT_SUCCESS;
}
