test_online_fetch__fetch_twice(void)
{
	git_remote *remote;
	cl_git_pass(git_remote_create(&remote, _repo, "test", "git://github.com/libgit2/TestGitRepository.git"));
    	cl_git_pass(git_remote_connect(remote, GIT_DIRECTION_FETCH));
    	cl_git_pass(git_remote_download(remote, NULL));
    	git_remote_disconnect(remote);

    	git_remote_connect(remote, GIT_DIRECTION_FETCH);
	cl_git_pass(git_remote_download(remote, NULL));
	git_remote_disconnect(remote);

	git_remote_free(remote);
}
