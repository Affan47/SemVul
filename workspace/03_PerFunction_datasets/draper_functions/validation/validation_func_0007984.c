__connman_private_network_release(const char *path)
{
	struct connman_private_network *pn;

	pn = g_hash_table_lookup(pn_hash, path);
	if (pn == NULL)
		return -EACCES;

	g_hash_table_remove(pn_hash, path);
	return 0;
}
