test_merge_trees_automerge__automerge(void)
{
	git_index *index;
	const git_index_entry *entry;
	git_merge_tree_opts opts = GIT_MERGE_TREE_OPTS_INIT;
	git_blob *blob;

	struct merge_index_entry merge_index_entries[] = {
		ADDED_IN_MASTER_INDEX_ENTRY,
		AUTOMERGEABLE_INDEX_ENTRY,
		CHANGED_IN_BRANCH_INDEX_ENTRY,
		CHANGED_IN_MASTER_INDEX_ENTRY,

		{ 0100644, "d427e0b2e138501a3d15cc376077a3631e15bd46", 1, "conflicting.txt" },
		{ 0100644, "4e886e602529caa9ab11d71f86634bd1b6e0de10", 2, "conflicting.txt" },
		{ 0100644, "2bd0a343aeef7a2cf0d158478966a6e587ff3863", 3, "conflicting.txt" },

		UNCHANGED_INDEX_ENTRY,
    };

	struct merge_reuc_entry merge_reuc_entries[] = {
		AUTOMERGEABLE_REUC_ENTRY,
		REMOVED_IN_BRANCH_REUC_ENTRY,
		REMOVED_IN_MASTER_REUC_ENTRY
	};

	cl_git_pass(merge_trees_from_branches(&index, repo, "master", THEIRS_AUTOMERGE_BRANCH, &opts));

	cl_assert(merge_test_index(index, merge_index_entries, 8));
	cl_assert(merge_test_reuc(index, merge_reuc_entries, 3));

	cl_assert((entry = git_index_get_bypath(index, "automergeable.txt", 0)) != NULL);
	cl_assert(entry->file_size == strlen(AUTOMERGEABLE_MERGED_FILE));

	cl_git_pass(git_object_lookup((git_object **)&blob, repo, &entry->oid, GIT_OBJ_BLOB));
	cl_assert(memcmp(git_blob_rawcontent(blob), AUTOMERGEABLE_MERGED_FILE, entry->file_size) == 0);

	git_index_free(index);
	git_blob_free(blob);
}
