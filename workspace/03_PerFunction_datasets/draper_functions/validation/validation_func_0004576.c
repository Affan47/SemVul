ensure_no_refname_starts_with_a_forward_slash(const char *path)
{
	size_t i;

	cl_git_pass(git_repository_open(&repo, path));
	cl_git_pass(git_reference_list(&ref_list, repo));

	cl_assert(ref_list.count > 0);

	for (i = 0; i < ref_list.count; i++)
		cl_assert(git__prefixcmp(ref_list.strings[i], "/") != 0);

	git_strarray_free(&ref_list);
	git_repository_free(repo);
}
