hostset_insert(hostset_t set, const char *hosts)
{
	int i, n = 0;
	hostlist_t hl = hostlist_create(hosts);
	if (!hl)
		return 0;

	hostlist_uniq(hl);
	LOCK_HOSTLIST(set->hl);
	for (i = 0; i < hl->nranges; i++)
		n += hostset_insert_range(set, hl->hr[i]);
	UNLOCK_HOSTLIST(set->hl);
	hostlist_destroy(hl);
	return n;
}
