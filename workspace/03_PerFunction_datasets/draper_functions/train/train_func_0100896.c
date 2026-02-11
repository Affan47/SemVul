assert_user_dir ()
{
	GDir *dh;

	dh = g_dir_open (main_path_user (), 0, NULL);
	if (dh == NULL)
	{
		g_message ("creating an empty user folder:\n %s", main_path_user ());
		g_mkdir (main_path_user (), DIR_PERM);
		dh = g_dir_open (main_path_user (), 0, NULL);
		if (dh == NULL)
			g_error ("could not creat a user folder, so we must quit!");
	}
	g_dir_close (dh);
}
