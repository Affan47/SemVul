static NOINLINE mstate FindMSpace(nedpool *RESTRICT p, threadcache *RESTRICT tc, int *RESTRICT lastUsed, size_t size) THROWSPEC
{


	int n, end;
	n=end=*lastUsed+1;
#if USE_LOCKS
	for(; p->m[n]; end=++n)
	{
		if(TRY_LOCK(&p->m[n]->mutex)) goto found;
	}
	for(n=0; n<*lastUsed && p->m[n]; n++)
	{
		if(TRY_LOCK(&p->m[n]->mutex)) goto found;
	}
	if(end<p->threads)
	{
		mstate temp;
#if USE_ALLOCATOR==0
		temp=(mstate) mspacecounter++;
#elif USE_ALLOCATOR==1
		if(!(temp=(mstate) create_mspace(size, 1)))
			goto badexit;
#endif

		ACQUIRE_LOCK(&p->mutex);
		while(p->m[end] && end<p->threads)
			end++;
		if(end>=p->threads)
		{
			RELEASE_LOCK(&p->mutex);
#if USE_ALLOCATOR==1
			destroy_mspace((mstate) temp);
#endif
			goto badexit;
		}


		{
			volatile struct malloc_state **_m=(volatile struct malloc_state **) &p->m[end];
			*_m=(p->m[end]=temp);
		}
		ACQUIRE_LOCK(&p->m[end]->mutex);

		RELEASE_LOCK(&p->mutex);
		n=end;
		goto found;
	}

badexit:
	ACQUIRE_LOCK(&p->m[*lastUsed]->mutex);
	return p->m[*lastUsed];
#endif
found:
	*lastUsed=n;
	if(tc)
		tc->mymspace=n;
	else
	{
		if(TLSSET(p->mycache, (void *)(size_t)(-(n+1)))) abort();
	}
	return p->m[n];
}
