xfl_replace_pointer_array(struct xfreelist *fl, void **array, size_t len)
{
	size_t used, size, capacity, i;
	void *ptr;

	g_assert(array != NULL);
	g_assert(size_is_non_negative(len));
	g_assert(mutex_is_owned(&fl->lock));
	g_assert(size_is_non_negative(fl->count));

	ptr = fl->pointers;
	used = sizeof(void *) * fl->count;
	size = sizeof(void *) * fl->capacity;
	capacity = len / sizeof(void *);

	g_assert(ptr != NULL || 0 == used);
	g_assert(len >= used);
	g_assert(capacity * sizeof(void *) == len);
	g_assert(array != ptr);

	for (i = fl->count; i < capacity; i++) {
		array[i] = XM_INVALID_PTR;
	}

	memcpy(array, ptr, used);
	fl->pointers = array;
	fl->capacity = capacity;

	g_assert(fl->capacity >= fl->count);


	if (ptr != NULL)
		xmalloc_freelist_add(ptr, size, XM_COALESCE_ALL);
}
