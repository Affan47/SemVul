gc_master_provider_initialize_geoclue (GcMasterProvider *master_provider)
{
	GcMasterProviderPrivate *priv = GET_PRIVATE (master_provider);
	GeoclueProvider *geoclue;
	GError *error = NULL;

	geoclue = gc_master_provider_get_provider (master_provider);

	if (!geoclue_provider_set_options (geoclue,
	                                   geoclue_get_main_options (),
	                                   &error)) {
		g_warning ("Error setting provider options: %s\n", error->message);
		g_error_free (error);
		return FALSE;
	}


	if (!geoclue_provider_get_provider_info (geoclue, NULL,
	                                         &priv->description, &error)) {
		g_warning ("Error getting provider info: %s\n", error->message);
		g_error_free (error);
		return FALSE;
	}

	g_signal_connect (G_OBJECT (geoclue), "status-changed",
			  G_CALLBACK (provider_status_changed), master_provider);


	if (!geoclue_provider_get_status (geoclue, &priv->status, &error)) {
		g_warning ("Error getting provider status: %s\n", error->message);
		g_error_free (error);
		return FALSE;
	}
	return TRUE;
}
