static NOINLINE void GetThreadCache_cold2(nedpool *RESTRICT *RESTRICT p, threadcache *RESTRICT *RESTRICT tc, int *RESTRICT mymspace, int mycache) THROWSPEC
{
	if(!mycache)
	{
		*tc=AllocCache(*p);
		if(!*tc)
		{
			if(TLSSET((*p)->mycache, (void *)(size_t)-1)) abort();
			*mymspace=0;
		}
		else
			*mymspace=(*tc)->mymspace;
	}
	else
	{
		*tc=0;
		*mymspace=-mycache-1;
	}
}
