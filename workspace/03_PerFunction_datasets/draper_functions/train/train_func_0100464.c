parse_options (int *argc,
               char ***argv)
{
	GError *error = NULL;
	GOptionContext *context;

	context = g_option_context_new ("- git config tool");

	g_option_context_set_ignore_unknown_options (context, TRUE);
	g_option_context_add_main_entries (context, entries, "gitg");

	if (!g_option_context_parse (context, argc, argv, &error))
	{
		g_print ("option parsing failed: %s\n", error->message);
		g_error_free (error);

		exit (1);
	}

	g_option_context_free (context);
}
