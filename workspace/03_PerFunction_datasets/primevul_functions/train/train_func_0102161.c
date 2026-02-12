int is_bare_repository(void)
{

	return is_bare_repository_cfg && !get_git_work_tree();
}
