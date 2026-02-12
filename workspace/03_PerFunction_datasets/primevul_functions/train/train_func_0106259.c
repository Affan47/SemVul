static int reuse_worktree_file(const char *name, const unsigned char *sha1, int want_file)
{
	struct cache_entry *ce;
	struct stat st;
	int pos, len;


	if (!active_cache)
		return 0;


	if (!FAST_WORKING_DIRECTORY && !want_file && has_sha1_pack(sha1, NULL))
		return 0;

	len = strlen(name);
	pos = cache_name_pos(name, len);
	if (pos < 0)
		return 0;
	ce = active_cache[pos];


	if (hashcmp(sha1, ce->sha1) || !S_ISREG(ce->ce_mode))
		return 0;


	if (ce_uptodate(ce) ||
	    (!lstat(name, &st) && !ce_match_stat(ce, &st, 0)))
		return 1;

	return 0;
}
