ensure_color_scheme_id (GeditPreferencesDialog *dlg,
			const gchar            *id)
{
	GtkSourceStyleSchemeManager *manager;
	GtkSourceStyleScheme *scheme = NULL;

	manager = gtk_source_style_scheme_manager_get_default ();
	if (id == NULL)
	{
		gchar *pref_id;

		pref_id = g_settings_get_string (dlg->priv->editor,
						 GEDIT_SETTINGS_SCHEME);

		scheme = gtk_source_style_scheme_manager_get_scheme (manager,
								     pref_id);
		g_free (pref_id);
	}
	else
	{
		scheme = gtk_source_style_scheme_manager_get_scheme (manager,
								     id);
	}

	if (scheme == NULL)
	{

		scheme = gtk_source_style_scheme_manager_get_scheme (manager,
								     "classic");
	}

	if (scheme == NULL)
	{

		return NULL;
	}

	return 	gtk_source_style_scheme_get_id (scheme);
}
