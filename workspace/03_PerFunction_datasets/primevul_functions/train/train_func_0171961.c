static NEDMALLOCNOALIASATTR mstate nedblkmstate(void *RESTRICT mem) THROWSPEC
{
	if(mem)
	{
#if USE_MAGIC_HEADERS
		size_t *_mem=(size_t *) mem-3;
		if(_mem[0]==*(size_t *) "NEDMALOC")
		{
			return (mstate) _mem[1];
		}
		else return 0;
#else
#if USE_ALLOCATOR==0

		return 0;
#elif USE_ALLOCATOR==1
#ifdef ENABLE_FAST_HEAP_DETECTION
#ifdef WIN32


#pragma pack(push, 1)
		struct _HEAP_ENTRY
		{
			USHORT Size;
			USHORT PreviousSize;
			UCHAR Cookie;
			UCHAR Flags;
			UCHAR UnusedBytes;
			UCHAR SmallTagIndex;
		} *RESTRICT he=((struct _HEAP_ENTRY *) mem)-1;
#pragma pack(pop)
		unsigned int header=((unsigned int *)mem)[-1], mask1=0x8080E100, result1, mask2=0xFFFFFF06, result2;
		result1=header & mask1;
		result2=header & mask2;
		if(result1==0x00000100 && result2!=0x00000102)
		{
			return 0;
		}
#endif
#ifdef __linux__


		mchunkptr p=mem2chunk(mem);
		mstate fm=get_mstate_for(p);

		if(!is_aligned(fm)) return 0;
		if((size_t)mem-(size_t)fm>=(size_t)1<<(SIZE_T_BITSIZE-1)) return 0;
		if(ok_magic(fm))
			return fm;
		else
			return 0;
		if(1) { }
#endif
		else
		{
			mchunkptr p=mem2chunk(mem);
			mstate fm=get_mstate_for(p);
			assert(ok_magic(fm));
			if(ok_magic(fm))
				return fm;
		}
#else
#ifdef WIN32
#ifdef _MSC_VER
		__try
#elif defined(__MINGW32__)
		__try1
#endif
#endif
		{


			register void *RESTRICT leastusedaddress_=leastusedaddress;
			register size_t largestusedblock_=largestusedblock;
			if(!is_aligned(mem)) return 0;
			if(mem<leastusedaddress_) return 0;
			{
				mchunkptr p=mem2chunk(mem);
				mstate fm=0;
				int ismmapped=is_mmapped(p);
				if((!ismmapped && !is_inuse(p)) || (p->head & FLAG4_BIT)) return 0;


				if(chunksize(p)-overhead_for(p)>largestusedblock_) return 0;


				if(!ismmapped && (!next_pinuse(p) || (next_chunk(p)->head & FLAG4_BIT))) return 0;

#if 0

				if(!ismmapped && !pinuse(p))
					if(next_chunk(prev_chunk(p))!=p) return 0;

#endif
				fm = get_mstate_for(p);
				if(!is_aligned(fm) || (void *)fm<leastusedaddress_) return 0;
#if 0

				if((size_t)mem-(size_t)fm>=(size_t)1<<(SIZE_T_BITSIZE-1)) return 0;
#endif
				assert(ok_magic(fm));
				if(ok_magic(fm))
					return fm;
			}
		}
#ifdef WIN32
#ifdef _MSC_VER
		__except(1) { }
#elif defined(__MINGW32__)
		__except1(1) { }
#endif
#endif
#endif
#endif
#endif
	}
	return 0;
}
