static void do_oneway_diff(struct unpack_trees_options *o,
	struct cache_entry *idx,
	struct cache_entry *tree)
{
	struct oneway_unpack_data *cbdata = o->unpack_data;
	struct rev_info *revs = cbdata->revs;
	int match_missing, cached;


	cached = o->index_only;
	match_missing = !revs->ignore_merges;

	if (cached && idx && ce_stage(idx)) {
		if (tree)
			diff_unmerge(&revs->diffopt, idx->name, idx->ce_mode, idx->sha1);
		return;
	}


	if (!tree) {
		show_new_file(cbdata, idx, cached, match_missing);
		return;
	}


	if (!idx) {
		diff_index_show_file(revs, "-", tree, tree->sha1, tree->ce_mode);
		return;
	}


	show_modified(cbdata, tree, idx, 1, cached, match_missing);
}
