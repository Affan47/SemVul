set_connection_device (MyApp *app)
{
	int ctype;
	char *dev = NULL;
	gboolean changed;

	ctype = gconf_client_get_int (app->client,
				      CONFBASE"/connection_type", NULL);
	changed = FALSE;

	switch (ctype) {
		case CONNECTION_BLUETOOTH:
			dev = gconf_client_get_string (app->client,
						       CONFBASE"/bluetooth_addr",
						       NULL);
			if (!dev || strlen (dev) != 17) {
				g_free (dev);
				dev = NULL;
			}
			break;
		case CONNECTION_SERIAL1:
			dev = g_strdup ("/dev/ttyS0");
			break;
		case CONNECTION_SERIAL2:
			dev = g_strdup ("/dev/ttyS1");
			break;
		case CONNECTION_IRCOMM:
			dev = g_strdup ("/dev/ircomm0");
			break;
		case CONNECTION_OTHER:
			dev = gconf_client_get_string (app->client,
					CONFBASE"/other_serial", NULL);
			break;
	}

	if (dev == NULL && app->devname != NULL)
		changed = TRUE;
	else if (dev != NULL && app->devname == NULL)
		changed = TRUE;
	else if (dev != NULL && app->devname != NULL && strcmp (dev, app->devname) != 0)
		changed = TRUE;

	g_free (app->devname);
	app->devname = dev;

	g_message ("New connection device is %s (%s)",
		   dev ? dev : "empty",
		   changed ? "changed" : "not changed");

	return changed;
}
