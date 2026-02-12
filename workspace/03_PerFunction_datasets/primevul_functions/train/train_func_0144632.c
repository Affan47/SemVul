static void cache_cleanup(void)
{
	static int max_timeout;
	struct cache_timeout data;
	int count = 0;

	data.current_time = time(NULL);
	data.max_timeout = 0;
	data.try_harder = 0;


	if (max_timeout <= data.current_time) {
		count = g_hash_table_foreach_remove(cache, cache_check_entry,
						&data);
	}
	debug("removed %d in the first pass", count);


	data.try_harder = 1;
	if (count == 0)
		count = g_hash_table_foreach_remove(cache, cache_check_entry,
						&data);

	if (count == 0)


		max_timeout = data.max_timeout;
	else
		max_timeout = 0;
}
