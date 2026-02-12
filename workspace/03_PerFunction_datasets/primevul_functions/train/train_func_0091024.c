int git_tree_entry_bypath(
	git_tree_entry **entry_out,
	const git_tree *root,
	const char *path)
{
	int error = 0;
	git_tree *subtree;
	const git_tree_entry *entry;
	size_t filename_len;


	filename_len = subpath_len(path);

	if (filename_len == 0) {
		giterr_set(GITERR_TREE, "Invalid tree path given");
		return GIT_ENOTFOUND;
	}

	entry = entry_fromname(root, path, filename_len);

	if (entry == NULL) {
		giterr_set(GITERR_TREE,
			"The path '%s' does not exist in the given tree", path);
		return GIT_ENOTFOUND;
	}

	switch (path[filename_len]) {
	case '/':


		if (!git_tree_entry__is_tree(entry)) {
			giterr_set(GITERR_TREE,
				"The path '%s' does not exist in the given tree", path);
			return GIT_ENOTFOUND;
		}


		if (path[filename_len + 1] != '\0')
			break;

	case '\0':


		return git_tree_entry_dup(entry_out, entry);
	}

	if (git_tree_lookup(&subtree, root->object.repo, &entry->oid) < 0)
		return -1;

	error = git_tree_entry_bypath(
		entry_out,
		subtree,
		path + filename_len + 1
	);

	git_tree_free(subtree);
	return error;
}
