_e2p_diff_twcb (VPATH *localpath,
	const struct stat *statptr, E2_TwStatus status, E2_CmpData *twdata)
{
	gchar *localotherpath;
	E2_TwResult retval = E2TW_STOP;
#ifdef E2_VFS
	VPATH ddata;
#endif

	switch (status)
	{
		case E2TW_F:
		case E2TW_SL:
		case E2TW_SLN:
			localotherpath = e2_utils_strcat (twdata->newroot,
				(gchar *)localpath + twdata->oldroot_len);
#ifdef E2_VFS
			ddata.localpath = localotherpath;
			ddata.spacedata = twdata->otherspace;
			if (_e2p_diff1 (localpath, statptr, &ddata))
#else
			if (_e2p_diff1 (localpath, statptr, localotherpath))
#endif
				retval = E2TW_CONTINUE;
			g_free (localotherpath);
			break;
		case E2TW_D:
		case E2TW_DRR:
		{
			struct stat othrstatbuf;
			localotherpath = e2_utils_strcat (twdata->newroot,
				(gchar *)localpath + twdata->oldroot_len);
#ifdef E2_VFS
			ddata.localpath = localotherpath;
			ddata.spacedata = twdata->otherspace;
			if (e2_fs_stat (&ddata, &othrstatbuf E2_ERR_NONE())
#else
			if (e2_fs_stat (localotherpath, &othrstatbuf E2_ERR_NONE())
#endif
				|| !S_ISDIR (othrstatbuf.st_mode)
				|| S_ISLNK (othrstatbuf.st_mode))
				break;


			guint count = 0;
			e2_fs_tw (localpath, _e2p_diff_count_twcb, &count, 1,
				E2TW_XQT | E2TW_PHYS E2_ERR_NONE());
			guint count2 = 0;
			localotherpath = e2_utils_strcat (twdata->newroot,
				(gchar *)localpath + twdata->oldroot_len);
#ifdef E2_VFS
			e2_fs_tw (&ddata, _e2p_diff_count_twcb, &count2, 1,
#else
			e2_fs_tw (localotherpath, _e2p_diff_count_twcb, &count2, 1,
#endif
				E2TW_XQT | E2TW_PHYS E2_ERR_NONE());
			g_free (localotherpath);
			if (count != count2)
				break;
		}
		case E2TW_DP:
			retval = E2TW_CONTINUE;
			break;


		default:
			break;
	}
	return retval;
}
