static int check_removed(const struct cache_entry *ce, struct stat *st)
{
	if (lstat(ce->name, st) < 0) {
		if (errno != ENOENT && errno != ENOTDIR)
			return -1;
		return 1;
	}
	if (has_symlink_leading_path(ce_namelen(ce), ce->name))
		return 1;
	if (S_ISDIR(st->st_mode)) {
		unsigned char sub[20];


		if (!S_ISGITLINK(ce->ce_mode) &&
		    resolve_gitlink_ref(ce->name, "HEAD", sub))
			return 1;
	}
	return 0;
}
