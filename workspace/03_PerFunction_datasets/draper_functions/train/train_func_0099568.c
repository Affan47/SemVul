test_stash_save__does_not_keep_index_by_default(void)
{


	unsigned int status;

	cl_git_pass(git_stash_save(&stash_tip_oid, repo, signature, NULL, GIT_STASH_DEFAULT));
	cl_git_pass(git_status_file(&status, repo, "when"));

	assert_blob_oid("refs/stash:what", "bc99dc98b3eba0e9157e94769cd4d49cb49de449");
	assert_blob_oid("refs/stash:how", "e6d64adb2c7f3eb8feb493b556cc8070dca379a3");
	assert_blob_oid("refs/stash:who", "a0400d4954659306a976567af43125a0b1aa8595");
	assert_blob_oid("refs/stash:when", NULL);
	assert_blob_oid("refs/stash:just.ignore", NULL);

	assert_blob_oid("refs/stash^2:what", "dd7e1c6f0fefe118f0b63d9f10908c460aa317a6");
	assert_blob_oid("refs/stash^2:how", "e6d64adb2c7f3eb8feb493b556cc8070dca379a3");
	assert_blob_oid("refs/stash^2:who", "cc628ccd10742baea8241c5924df992b5c019f71");
	assert_blob_oid("refs/stash^2:when", NULL);
	assert_blob_oid("refs/stash^2:just.ignore", NULL);

	assert_blob_oid("refs/stash^3", NULL);

	cl_assert_equal_i(GIT_STATUS_WT_NEW, status);
}
