static void pageset_update(struct per_cpu_pages *pcp, unsigned long high,
		unsigned long batch)
{

	pcp->batch = 1;
	smp_wmb();


	pcp->high = high;
	smp_wmb();

	pcp->batch = batch;
}
