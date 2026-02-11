xcalloc(size_t nmemb, size_t size)
{
	void *ret = calloc(nmemb, size);
	if (!ret && (!nmemb || !size))
		ret = calloc(1, 1);
	if (!ret) {
		release_pack_memory(nmemb * size, -1);
		ret = calloc(nmemb, size);
		if (!ret && (!nmemb || !size))
			ret = calloc(1, 1);
		if (!ret)
			die("Out of memory, calloc failed");
	}
	return ret;
}
