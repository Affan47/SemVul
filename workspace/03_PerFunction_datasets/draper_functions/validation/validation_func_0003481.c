hce_alloc(void)
{
	static const hostcache_entry_t zero_hce;
	hostcache_entry_t *hce;

	WALLOC(hce);
	*hce = zero_hce;
	return hce;
}
