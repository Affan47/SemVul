static inline void mm_populate(unsigned long addr, unsigned long len)
{

	(void) __mm_populate(addr, len, 1);
}
