layout_editors_reload_idle_cb(gpointer data)
{
	if (!layout_editors_desktop_files)
		{
		DEBUG_1("%s layout_editors_reload_idle_cb: get_desktop_files", get_exec_time());
		layout_editors_desktop_files = editor_get_desktop_files();
		return TRUE;
		}

	editor_read_desktop_file(layout_editors_desktop_files->data);
	g_free(layout_editors_desktop_files->data);
	layout_editors_desktop_files = g_list_delete_link(layout_editors_desktop_files, layout_editors_desktop_files);


	if (!layout_editors_desktop_files)
		{
		GList *work;
		DEBUG_1("%s layout_editors_reload_idle_cb: setup_editors", get_exec_time());
		editor_table_finish();

		work = layout_window_list;
		while (work)
			{
			LayoutWindow *lw = work->data;
			work = work->next;
			layout_actions_setup_editors(lw);
			}

		DEBUG_1("%s layout_editors_reload_idle_cb: setup_editors done", get_exec_time());

		layout_editors_reload_idle_id = -1;
		return FALSE;
		}
	return TRUE;
}
