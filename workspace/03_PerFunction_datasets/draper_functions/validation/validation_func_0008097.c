git_futils_mkpath2file(const char *file_path, const mode_t mode)
{
	int result = 0;
	git_buf target_folder = GIT_BUF_INIT;

	if (git_path_dirname_r(&target_folder, file_path) < 0)
		return -1;


	if (git_path_isdir(target_folder.ptr) == false)

		result = git_futils_mkdir_r(target_folder.ptr, NULL, mode);

	git_buf_free(&target_folder);
	return result;
}
