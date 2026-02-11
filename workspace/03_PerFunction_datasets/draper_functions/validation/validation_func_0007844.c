workdir_iterator__update_entry(fs_iterator *fi)
{
	workdir_iterator *wi = (workdir_iterator *)fi;


	if (workdir_path_is_dotgit(&fi->path))
		return GIT_ENOTFOUND;


	wi->is_ignored = GIT_IGNORE_UNCHECKED;

	return 0;
}
