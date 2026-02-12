static int zone_batchsize(struct zone *zone)
{
#ifdef CONFIG_MMU
	int batch;


	batch = zone->managed_pages / 1024;
	if (batch * PAGE_SIZE > 512 * 1024)
		batch = (512 * 1024) / PAGE_SIZE;
	batch /= 4;
	if (batch < 1)
		batch = 1;


	batch = rounddown_pow_of_two(batch + batch/2) - 1;

	return batch;

#else


	return 0;
#endif
}
