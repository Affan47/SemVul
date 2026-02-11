__check_element(mempool_t *pool, void *element, size_t size)
{
	u8 *obj = element;
	size_t i;

	for (i = 0; i < size; i++) {
		u8 exp = (i < size - 1) ? POISON_FREE : POISON_END;

		if (obj[i] != exp) {
			poison_error(pool, element, size, i);
			return;
		}
	}
	memset(obj, POISON_INUSE, size);
}
