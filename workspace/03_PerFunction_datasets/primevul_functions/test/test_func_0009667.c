void rtrs_clt_close(struct rtrs_clt_sess *clt)
{
	struct rtrs_clt_path *clt_path, *tmp;


	rtrs_clt_destroy_sysfs_root(clt);


	list_for_each_entry_safe(clt_path, tmp, &clt->paths_list, s.entry) {
		rtrs_clt_close_conns(clt_path, true);
		rtrs_clt_destroy_path_files(clt_path, NULL);
		kobject_put(&clt_path->kobj);
	}
	free_clt(clt);
}
