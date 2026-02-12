static NOINLINE void ReleaseFreeInCache(nedpool *RESTRICT p, threadcache *RESTRICT tc, int mymspace) THROWSPEC
{
	unsigned int age=THREADCACHEMAXFREESPACE/8192;
#if USE_LOCKS

#endif
	while(age && tc->freeInCache>=THREADCACHEMAXFREESPACE)
	{
		RemoveCacheEntries(p, tc, age);

		age>>=1;
	}
#if USE_LOCKS

#endif
}
