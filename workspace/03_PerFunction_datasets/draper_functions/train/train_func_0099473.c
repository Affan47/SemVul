_e2p_find_dofind (E2_FindDialogRuntime *rt)
{
	if (rt == NULL)
		return NULL;

	pthread_cleanup_push ((gpointer)_e2p_find_cleanfind, (gpointer)rt);
	pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	e2_utils_block_thread_signals ();

	findtargets *fdata = rt->matchdata;

#ifdef TRACKERFIND
	if (fdata->contentop == TRAK || fdata->typeop == TRAK)
	{
		_e2p_find_tracker_find (
#ifdef E2_VFS
		fdata->sdata,
#else
		fdata->localstartpath,
#endif
		fdata->searchdepth, fdata);
	}
	else
	{
#endif
		e2_fs_tw (
#ifdef E2_VFS
		fdata->sdata,
#else
		fdata->localstartpath,
#endif
		_e2p_find_twcb, fdata, fdata->searchdepth,
		E2TW_XQT | E2TW_NODIR | E2TW_PHYS E2_ERR_NONE());

		if (fdata->dirdata != NULL)
		{
			GList *member;
			E2_DirEnt *dirfix;
			for (member = g_list_last (fdata->dirdata); member != NULL; member = member->prev)
			{
				dirfix = (E2_DirEnt *)member->data;
				if (dirfix != NULL)
				{
					E2_ERR_DECLARE;
#ifdef E2_VFS
					fdata->sdata.localpath = dirfix->path;
					if (e2_fs_chmod (fdata->sdata, dirfix->mode E2_ERR_PTR())
#else
					if (e2_fs_chmod (dirfix->path, dirfix->mode E2_ERR_PTR())
#endif
							&& E2_ERR_ISNOT (ENOENT))
					{
						e2_fs_error_local (_("Cannot change permissions of %s"),
#ifdef E2_VFS
								fdata->sdata E2_ERR_MSGL());
#else
								dirfix->path E2_ERR_MSGL());
#endif
					}
					g_free (dirfix->path);
					DEALLOCATE (E2_DirEnt, dirfix);
				}
			}
			g_list_free (fdata->dirdata);
		}
#ifdef TRACKERFIND
	}
#endif
	gdk_threads_enter ();
	e2_output_print_end (&app.tab, FALSE);
	gdk_threads_leave ();
	_e2p_find_reset_widgets (rt);

	pthread_cleanup_pop (1);

	return NULL;
}
