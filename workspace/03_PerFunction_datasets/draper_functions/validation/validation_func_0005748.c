je_aligned_alloc(size_t alignment, size_t size)
{
	void *ret;
	int err;

	if ((err = imemalign(&ret, alignment, size, 1)) != 0) {
		ret = NULL;
		set_errno(err);
	}
	JEMALLOC_VALGRIND_MALLOC(err == 0, ret, isalloc(ret, config_prof),
	    false);
	return (ret);
}
