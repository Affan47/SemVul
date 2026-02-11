test_merge_workdir_setup__two_remote_tracking_branch_and_two_normal_branches(void)
{
	git_oid our_oid;
	git_reference *octo1_ref;
	git_reference *octo2_ref;
	git_reference *octo3_ref;
	git_reference *octo4_ref;
	git_merge_head *our_head, *their_heads[4];

	cl_git_pass(create_remote_tracking_branch(OCTO2_BRANCH, OCTO2_OID));
	cl_git_pass(create_remote_tracking_branch(OCTO4_BRANCH, OCTO4_OID));

	cl_git_pass(git_oid_fromstr(&our_oid, ORIG_HEAD));
	cl_git_pass(git_merge_head_from_oid(&our_head, repo, &our_oid));

	cl_git_pass(git_reference_lookup(&octo1_ref, repo, GIT_REFS_HEADS_DIR OCTO1_BRANCH));
	cl_git_pass(git_merge_head_from_ref(&their_heads[0], repo, octo1_ref));

	cl_git_pass(git_reference_lookup(&octo2_ref, repo, GIT_REFS_REMOTES_DIR "origin/" OCTO2_BRANCH));
	cl_git_pass(git_merge_head_from_ref(&their_heads[1], repo, octo2_ref));

	cl_git_pass(git_reference_lookup(&octo3_ref, repo, GIT_REFS_HEADS_DIR OCTO3_BRANCH));
	cl_git_pass(git_merge_head_from_ref(&their_heads[2], repo, octo3_ref));

	cl_git_pass(git_reference_lookup(&octo4_ref, repo, GIT_REFS_REMOTES_DIR "origin/" OCTO4_BRANCH));
	cl_git_pass(git_merge_head_from_ref(&their_heads[3], repo, octo4_ref));

	cl_git_pass(git_merge__setup(repo, our_head, (const git_merge_head **)their_heads, 4, 0));

	cl_assert(test_file_contents(GIT_MERGE_HEAD_FILE, OCTO1_OID "\n" OCTO2_OID "\n" OCTO3_OID "\n" OCTO4_OID "\n"));
	cl_assert(test_file_contents(GIT_ORIG_HEAD_FILE, ORIG_HEAD "\n"));
	cl_assert(test_file_contents(GIT_MERGE_MODE_FILE, ""));
	cl_assert(test_file_contents(GIT_MERGE_MSG_FILE, "Merge branches '" OCTO1_BRANCH "' and '" OCTO3_BRANCH "', remote-tracking branches 'refs/remotes/origin/" OCTO2_BRANCH "' and 'refs/remotes/origin/" OCTO4_BRANCH "'\n"));

	git_reference_free(octo1_ref);
	git_reference_free(octo2_ref);
	git_reference_free(octo3_ref);
	git_reference_free(octo4_ref);

	git_merge_head_free(our_head);
	git_merge_head_free(their_heads[0]);
	git_merge_head_free(their_heads[1]);
	git_merge_head_free(their_heads[2]);
	git_merge_head_free(their_heads[3]);
}
