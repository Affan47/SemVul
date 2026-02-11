hexchat_pluginpref_get_str (hexchat_plugin *pl, const char *var, char *dest)
{
	int fh;
	int l;
	char confname[64];
	char *canon;
	char *cfg;
	struct stat st;

	canon = g_strdup (pl->name);
	canonalize_key (canon);
	sprintf (confname, "addon_%s.conf", canon);
	g_free (canon);


	fh = hexchat_open_file (confname, O_RDONLY, 0, 0);

	if (fh == -1)
	{
		return 0;
	}

	fstat (fh, &st);
	cfg = malloc (st.st_size + 1);

	if (!cfg)
	{
		close (fh);
		return 0;
	}

	cfg[0] = '\0';
	l = read (fh, cfg, st.st_size);

	if (l >= 0)
	{
		cfg[l] = '\0';
	}

	if (!cfg_get_str (cfg, var, dest, 512))
	{
		free (cfg);
		close (fh);
		return 0;
	}

	free (cfg);
	close (fh);
	return 1;
}
