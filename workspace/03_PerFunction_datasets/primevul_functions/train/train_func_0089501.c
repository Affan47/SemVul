int update_server_info(int force)
{


	int errs = 0;

	errs = errs | update_info_refs(force);
	errs = errs | update_info_packs(force);


	unlink_or_warn(git_path("info/rev-cache"));

	return errs;
}
