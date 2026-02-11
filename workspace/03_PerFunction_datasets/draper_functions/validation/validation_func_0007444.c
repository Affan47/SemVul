icase_exists(struct unpack_trees_options *o, struct cache_entry *dst, struct stat *st)
{
	struct cache_entry *src;

	src = index_name_exists(o->src_index, dst->name, ce_namelen(dst), 1);
	return src && !ie_match_stat(o->src_index, src, st, CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE);
}
