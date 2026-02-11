poldiff_bool_get_stats(const poldiff_t * diff, size_t stats[5])
{
	if (diff == NULL || stats == NULL) {
		ERR(diff, "%s", strerror(EINVAL));
		errno = EINVAL;
		return;
	}
	stats[0] = diff->bool_diffs->num_added;
	stats[1] = diff->bool_diffs->num_removed;
	stats[2] = diff->bool_diffs->num_modified;
	stats[3] = 0;
	stats[4] = 0;
}
