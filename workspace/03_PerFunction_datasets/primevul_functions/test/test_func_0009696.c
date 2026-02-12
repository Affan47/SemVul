int rtrs_clt_remove_path_from_sysfs(struct rtrs_clt_path *clt_path,
				     const struct attribute *sysfs_self)
{
	enum rtrs_clt_state old_state;
	bool changed;


	do {
		rtrs_clt_close_conns(clt_path, true);
		changed = rtrs_clt_change_state_get_old(clt_path,
							RTRS_CLT_DEAD,
							&old_state);
	} while (!changed && old_state != RTRS_CLT_DEAD);

	if (changed) {
		rtrs_clt_remove_path_from_arr(clt_path);
		rtrs_clt_destroy_path_files(clt_path, sysfs_self);
		kobject_put(&clt_path->kobj);
	}

	return 0;
}
