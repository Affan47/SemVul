static unsigned long shrink_huge_zero_page_count(struct shrinker *shrink,
					struct shrink_control *sc)
{

	return atomic_read(&huge_zero_refcount) == 1 ? HPAGE_PMD_NR : 0;
}
