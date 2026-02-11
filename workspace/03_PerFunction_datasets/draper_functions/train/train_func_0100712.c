secret_tool_action_lookup (int argc,
                           char *argv[])
{
	GError *error = NULL;
	GOptionContext *context;
	SecretService *service;
	GHashTable *attributes;
	SecretValue *value = NULL;

	context = g_option_context_new ("attribute value ...");
	g_option_context_add_main_entries (context, LOOKUP_OPTIONS, GETTEXT_PACKAGE);
	if (!g_option_context_parse (context, &argc, &argv, &error)) {
		g_printerr ("%s\n", error->message);
		usage();
	}

	g_option_context_free (context);

	attributes = attributes_from_arguments (attribute_args);
	g_strfreev (attribute_args);

	service = secret_service_get_sync (SECRET_SERVICE_NONE, NULL, &error);
	if (error == NULL)
		value = secret_service_lookup_sync (service, NULL, attributes, NULL, &error);

	g_object_unref (service);
	g_hash_table_unref (attributes);

	if (error != NULL) {
		g_printerr ("%s: %s\n", g_get_prgname (), error->message);
		return 1;
	}

	if (value == NULL)
		return 1;

	write_password_stdout (value);
	secret_value_unref (value);
	return 0;
}
