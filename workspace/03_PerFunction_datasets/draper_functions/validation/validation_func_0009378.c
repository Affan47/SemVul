panel_applet_container_child_property_get_info (const gchar *property_name)
{
	gint i;

	g_assert (property_name != NULL);

	for (i = 0; i < G_N_ELEMENTS (applet_properties); i++) {
		if (g_ascii_strcasecmp (applet_properties[i].name, property_name) == 0)
			return &applet_properties[i];
	}

	return NULL;
}
