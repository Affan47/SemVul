vflist_refresh(ViewFile *vf)
{
	GList *old_list;
	gboolean ret = TRUE;

	old_list = vf->list;
	vf->list = NULL;

	DEBUG_1("%s vflist_refresh: read dir", get_exec_time());
	if (vf->dir_fd)
		{
		file_data_unregister_notify_func(vf_notify_cb, vf);

		ret = filelist_read(vf->dir_fd, &vf->list, NULL);
		vf->list = file_data_filter_marks_list(vf->list, vf_marks_get_filter(vf));
		file_data_register_notify_func(vf_notify_cb, vf, NOTIFY_PRIORITY_MEDIUM);

		DEBUG_1("%s vflist_refresh: sort", get_exec_time());
		vf->list = filelist_sort(vf->list, vf->sort_method, vf->sort_ascend);
		}

	DEBUG_1("%s vflist_refresh: populate view", get_exec_time());

	vflist_populate_view(vf, FALSE);

	filelist_free(old_list);
	DEBUG_1("%s vflist_refresh: done", get_exec_time());

	return ret;
}
