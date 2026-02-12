xfs_max_file_offset(
	unsigned int		blockshift)
{
	unsigned int		pagefactor = 1;
	unsigned int		bitshift = BITS_PER_LONG - 1;


#if BITS_PER_LONG == 32
# if defined(CONFIG_LBDAF)
	ASSERT(sizeof(sector_t) == 8);
	pagefactor = PAGE_SIZE;
	bitshift = BITS_PER_LONG;
# else
	pagefactor = PAGE_SIZE >> (PAGE_SHIFT - blockshift);
# endif
#endif

	return (((uint64_t)pagefactor) << bitshift) - 1;
}
