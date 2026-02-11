config_new_stored (GnomeRRScreen *screen, const char *filename, GError **error)
{
    GnomeRRConfig *current;
    GnomeRRConfig **configs;
    GnomeRRConfig *result;

    g_return_val_if_fail (screen != NULL, NULL);
    g_return_val_if_fail (error == NULL || *error == NULL, NULL);

    current = gnome_rr_config_new_current (screen);

    configs = configurations_read_from_file (filename, error);

    result = NULL;
    if (configs)
    {
	int i;

	for (i = 0; configs[i] != NULL; ++i)
	{
	    if (gnome_rr_config_match (configs[i], current))
	    {
		result = gnome_rr_config_copy (configs[i]);
		break;
	    }
	}

	if (result == NULL)
	    g_set_error (error, GNOME_RR_ERROR, GNOME_RR_ERROR_NO_MATCHING_CONFIG,
			 _("none of the saved display configurations matched the active configuration"));

	configurations_free (configs);
    }

    gnome_rr_config_free (current);

    return result;
}
