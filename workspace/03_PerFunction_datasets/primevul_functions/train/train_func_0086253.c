static inline unsigned long get_mm_counter(struct mm_struct *mm, int member)
{
	long val = atomic_long_read(&mm->rss_stat.count[member]);

#ifdef SPLIT_RSS_COUNTING


	if (val < 0)
		val = 0;
#endif
	return (unsigned long)val;
}
