maki_remote_print_bus_address (void)
{
	gchar* bus_address;
	gchar* path;

	path = g_build_filename(g_get_user_config_dir(), "sushi", "bus_address", NULL);

	if (!g_file_get_contents(path, &bus_address, NULL, NULL))
	{
		bus_address = NULL;
	}

	g_free(path);

	return bus_address;
}
