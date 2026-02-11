show_files(struct dir_struct *dir)
{
	int i;


	if (show_others || show_killed) {
		fill_directory(dir, pathspec);
		if (show_others)
			show_other_files(dir);
		if (show_killed)
			show_killed_files(dir);
	}
	if (show_cached | show_stage) {
		for (i = 0; i < active_nr; i++) {
			struct cache_entry *ce = active_cache[i];
			int dtype = ce_to_dtype(ce);
			if (dir->flags & DIR_SHOW_IGNORED &&
			    !excluded(dir, ce->name, &dtype))
				continue;
			if (show_unmerged && !ce_stage(ce))
				continue;
			if (ce->ce_flags & CE_UPDATE)
				continue;
			show_ce_entry(ce_stage(ce) ? tag_unmerged :
				(ce_skip_worktree(ce) ? tag_skip_worktree : tag_cached), ce);
		}
	}
	if (show_deleted | show_modified) {
		for (i = 0; i < active_nr; i++) {
			struct cache_entry *ce = active_cache[i];
			struct stat st;
			int err;
			int dtype = ce_to_dtype(ce);
			if (dir->flags & DIR_SHOW_IGNORED &&
			    !excluded(dir, ce->name, &dtype))
				continue;
			if (ce->ce_flags & CE_UPDATE)
				continue;
			if (ce_skip_worktree(ce))
				continue;
			err = lstat(ce->name, &st);
			if (show_deleted && err)
				show_ce_entry(tag_removed, ce);
			if (show_modified && ce_modified(ce, &st, 0))
				show_ce_entry(tag_modified, ce);
		}
	}
}
