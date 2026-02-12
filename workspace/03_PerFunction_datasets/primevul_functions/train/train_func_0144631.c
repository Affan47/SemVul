static gboolean cache_invalidate_entry(gpointer key, gpointer value,
					gpointer user_data)
{
	struct cache_entry *entry = value;


	cache_enforce_validity(entry);


	if (entry->hits > 0 && (entry->ipv4 || entry->ipv6))
		entry->want_refresh = true;


	if (entry->ipv4) {
		g_free(entry->ipv4->data);
		g_free(entry->ipv4);
		entry->ipv4 = NULL;
	}

	if (entry->ipv6) {
		g_free(entry->ipv6->data);
		g_free(entry->ipv6);
		entry->ipv6 = NULL;
	}


	if (entry->want_refresh)
		return FALSE;
	else
		return TRUE;
}
