test_revwalk_signatureparsing__initialize(void)
{
	cl_git_pass(git_repository_open(&_repo, cl_fixture("testrepo.git")));
	cl_git_pass(git_revwalk_new(&_walk, _repo));
}
