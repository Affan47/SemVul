static bool _check_dir_contents(
	git_buf *dir,
	const char *sub,
	bool (*predicate)(const char *))
{
	bool result;
	size_t dir_size = git_buf_len(dir);
	size_t sub_size = strlen(sub);
	size_t alloc_size;


	if (GIT_ADD_SIZET_OVERFLOW(&alloc_size, dir_size, sub_size) ||
		GIT_ADD_SIZET_OVERFLOW(&alloc_size, alloc_size, 2) ||
		git_buf_try_grow(dir, alloc_size, false) < 0)
		return false;


	if (git_buf_joinpath(dir, dir->ptr, sub) < 0)
		return false;

	result = predicate(dir->ptr);


	git_buf_truncate(dir, dir_size);
	return result;
}
