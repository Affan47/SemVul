enter_initial_dirs(MainInfo *min, const gchar *dirleft, const gchar *dirright)
{
	const gchar	*dir;
	const gchar	*odir[2];
	const gchar	*cmd[] = { "ActivateLeft", "ActivateRight" };
	gint		i;
	gboolean	ok = TRUE;

	odir[0] = dirleft;
	odir[1] = dirright;
	for(i = sizeof cmd / sizeof *cmd - 1; i >= 0; i--)
	{
		if((dir = odir[i]) == NULL)
		{
			dir = min->cfg.dp_format[i].def_path;
			if(!dir[0])
				dir = dph_history_get_first(&min->gui->pane[i]);
		}
		if(dir == NULL)
			dir = usr_get_home();
		csq_execute(min, cmd[i]);
		ok &= csq_execute_format(min, "DirEnter 'dir=%s'", stu_escape(dir)) != 0;
	}

	return ok;
}
