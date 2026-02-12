NEDMALLOCNOALIASATTR NEDMALLOCPTRATTR void * nedprealloc(nedpool *p, void *mem, size_t size) THROWSPEC
{
	unsigned flags=NEDMALLOC_FORCERESERVE(p, mem, size);
#if ENABLE_USERMODEPAGEALLOCATOR


	if(8==sizeof(size_t) || !OSHavePhysicalPageSupport())
#endif
	{

		if(!(flags & M2_RESERVE_MASK)) flags=M2_RESERVE_MULT(8);
	}
	return nedprealloc2(p, mem, size, 0, flags);
}
