main (int   argc,
      char *argv[])
{
	TrackerConfig *config;
	TrackerController *controller;
	GOptionContext *context;
	GMainLoop *loop;
	GError *error = NULL;
	gchar *log_filename;
	guint shutdown_timeout;


	setlocale (LC_ALL, "");

	bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);


	context = g_option_context_new (_("- start the tracker writeback service"));

	g_option_context_add_main_entries (context, entries, NULL);
	g_option_context_parse (context, &argc, &argv, &error);
	g_option_context_free (context);

	if (version) {
		g_print ("\n" ABOUT "\n" LICENSE "\n");
		return EXIT_SUCCESS;
	}


	config = tracker_config_new ();

	if (verbosity > -1) {
		tracker_config_set_verbosity (config, verbosity);
	}

	tracker_log_init (tracker_config_get_verbosity (config),
	                  &log_filename);
	if (log_filename != NULL) {
		g_message ("Using log file:'%s'", log_filename);
		g_free (log_filename);
	}

	sanity_check_option_values (config);

	if (disable_shutdown) {
		shutdown_timeout = 0;
	} else {
		shutdown_timeout = QUIT_TIMEOUT;
	}

	controller = tracker_controller_new (shutdown_timeout, &error);

	if (error) {
		g_critical ("Error creating controller: %s", error->message);
		g_error_free (error);
		return EXIT_FAILURE;
	}

	g_message ("Main thread is: %p", g_thread_self ());

	loop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (loop);


	tracker_log_shutdown ();

	g_object_unref (controller);

	g_main_loop_unref (loop);

	g_object_unref (config);

	return EXIT_SUCCESS;
}
