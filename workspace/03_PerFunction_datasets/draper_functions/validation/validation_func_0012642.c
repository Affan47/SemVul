go_plugin_init (GOPlugin *plugin, GOCmdContext *cc)
{
	GIOChannel *channel = NULL;
	char *filename;

	debug = gnm_debug_flag ("datasource");

	if (debug)
		g_printerr (">>>>>>>>>>>>>>>>>>>>>>>>>>>> LOAD ATL\n");
	g_return_if_fail (atl_fd < 0);

	filename = g_build_filename (g_get_home_dir (), "atl", NULL);


#ifdef HAVE_MKFIFO
#warning "If gstdio.h had g_mkfifo, that's what we should use here"
	if (mkfifo (filename, S_IRUSR | S_IWUSR) == 0) {
		atl_filename = filename;
		atl_fd = g_open (atl_filename, O_RDWR|O_NONBLOCK, 0);
	} else
#endif
		g_free (filename);

	if (atl_fd >= 0) {
		atl_file = fdopen (atl_fd, "rb");
		channel = g_io_channel_unix_new (atl_fd);
		atl_source  = g_io_add_watch (channel,
			G_IO_IN | G_IO_ERR | G_IO_HUP | G_IO_NVAL,
			cb_atl_input, NULL);
		g_io_channel_unref (channel);
	}
	watched_values = g_hash_table_new (
		(GHashFunc)  g_str_hash,
		(GEqualFunc) g_str_equal);
	watchers = g_hash_table_new (
		(GHashFunc)  watcher_hash,
		(GEqualFunc) watcher_equal);
}
