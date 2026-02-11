test_refs_rename__force_loose(void)
{

	git_reference *looked_up_ref, *renamed_ref;
	git_oid oid;


	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, "refs/heads/br2"));
	git_oid_cpy(&oid, git_reference_target(looked_up_ref));


	cl_git_pass(git_reference_rename(&renamed_ref, looked_up_ref, "refs/heads/test", 1));
	git_reference_free(looked_up_ref);
	git_reference_free(renamed_ref);


	cl_git_pass(git_reference_lookup(&looked_up_ref, g_repo, "refs/heads/test"));
	cl_assert_equal_s(looked_up_ref->name,  "refs/heads/test");
	cl_assert(!git_oid_cmp(&oid, git_reference_target(looked_up_ref)));
	git_reference_free(looked_up_ref);


	cl_git_fail(git_reference_lookup(&looked_up_ref, g_repo, "refs/heads/br2"));

	git_reference_free(looked_up_ref);
}
