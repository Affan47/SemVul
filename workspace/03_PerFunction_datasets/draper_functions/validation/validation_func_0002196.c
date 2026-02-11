test_diff_blob__can_compare_two_binary_blobs(void)
{
	git_blob *heart;
	git_oid h_oid;


	cl_git_pass(git_oid_fromstrn(&h_oid, "de863bff", 8));
	cl_git_pass(git_blob_lookup_prefix(&heart, g_repo, &h_oid, 4));

	cl_git_pass(git_diff_blobs(
		alien, heart, &opts, &expected, diff_file_fn, diff_hunk_fn, diff_line_fn));

	assert_binary_blobs_comparison(expected);

	memset(&expected, 0, sizeof(expected));

	cl_git_pass(git_diff_blobs(
		heart, alien, &opts, &expected, diff_file_fn, diff_hunk_fn, diff_line_fn));

	assert_binary_blobs_comparison(expected);

	git_blob_free(heart);
}
