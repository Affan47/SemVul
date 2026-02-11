tiny_alloc_init(void *pool, unsigned long poolsize)
{

	unsigned long arrsize = free_array_size(poolsize);


	if (poolsize < MIN_BLOCK_SIZE)
		return;

	memset(pool, 0, arrsize);
	encode(poolsize - arrsize, true, (unsigned char *)pool + arrsize);
}
