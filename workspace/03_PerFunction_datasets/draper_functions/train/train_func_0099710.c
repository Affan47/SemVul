provider_changed_cb (GeoclueMasterClient *client,
                     char *iface,
                     char *name,
                     char *description,
                     gpointer userdata)
{
	if (strlen (name) == 0) {
		g_print ("No provider available\n");
	} else {
		g_print ("now using provider: %s\n", name);
	}
}
