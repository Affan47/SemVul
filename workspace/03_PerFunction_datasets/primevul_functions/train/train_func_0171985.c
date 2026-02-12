static FORCEINLINE mstate GetMSpace(nedpool *RESTRICT p, threadcache *RESTRICT tc, int mymspace, size_t size) THROWSPEC
{
	mstate m=p->m[mymspace];
	assert(m);
#if USE_LOCKS && USE_ALLOCATOR==1
	if(!TRY_LOCK(&p->m[mymspace]->mutex)) m=FindMSpace(p, tc, &mymspace, size);

#endif
	return m;
}
