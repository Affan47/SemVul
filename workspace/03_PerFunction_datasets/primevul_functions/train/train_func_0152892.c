static int set_max_cache_ids_by_cache(struct mdesc_handle *hp, int level)
{
	u64 mp;
	int idx = 1;
	int fnd = 0;


	mdesc_for_each_node_by_name(hp, mp, "cache") {
		const u64 *cur_lvl;

		cur_lvl = mdesc_get_property(hp, mp, "level", NULL);
		if (*cur_lvl != level)
			continue;
		mark_max_cache_ids(hp, mp, idx);
		idx++;
		fnd = 1;
	}
	return fnd;
}
