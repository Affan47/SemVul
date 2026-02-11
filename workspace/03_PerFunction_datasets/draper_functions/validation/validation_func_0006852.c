hostlist_push(hostlist_t hl, const char *hosts)
{
	hostlist_t new;
	int retval;
	if (!hosts || !hl)
		return 0;
	new = hostlist_create(hosts);
	if (!new)
		return 0;
	mutex_lock(&new->mutex);
	retval = new->nhosts;
	mutex_unlock(&new->mutex);
	hostlist_push_list(hl, new);
	hostlist_destroy(new);
	return retval;
}
