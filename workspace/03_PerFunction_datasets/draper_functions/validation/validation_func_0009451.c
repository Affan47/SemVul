bitflip_filter_apply(
	git_filter     *self,
	void          **payload,
	git_buf        *to,
	const git_buf  *from,
	const git_filter_source *source)
{
	const unsigned char *src = (const unsigned char *)from->ptr;
	unsigned char *dst;
	size_t i;

	GIT_UNUSED(self); GIT_UNUSED(payload);


	cl_assert_equal_i(
		0, git__strncmp("hero", git_filter_source_path(source), 4));

	if (!from->size)
		return 0;

	cl_git_pass(git_buf_grow(to, from->size));

	dst = (unsigned char *)to->ptr;

	for (i = 0; i < from->size; i++)
		dst[i] = VERY_SECURE_ENCRYPTION(src[i]);

	to->size = from->size;

	return 0;
}
