test_merge_trees_trivial__4(void)
{
	git_index *result;
	const git_index_entry *entry;

	cl_git_pass(merge_trivial(&result, "trivial-4", "trivial-4-branch", 0));

	cl_assert((entry = git_index_get_bypath(result, "new-and-different.txt", 0)) == NULL);
	cl_assert(git_index_reuc_entrycount(result) == 0);

	cl_assert(merge_trivial_conflict_entrycount(result) == 2);
	cl_assert(entry = git_index_get_bypath(result, "new-and-different.txt", 2));
	cl_assert(entry = git_index_get_bypath(result, "new-and-different.txt", 3));

	git_index_free(result);
}
