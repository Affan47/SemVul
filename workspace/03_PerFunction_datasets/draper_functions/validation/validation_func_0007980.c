gda_server_provider_get_data_handler_g_type (GdaServerProvider *provider, GdaConnection *cnc, GType for_type)
{
	GdaDataHandler *retval = NULL;
	g_return_val_if_fail (GDA_IS_SERVER_PROVIDER (provider), NULL);
	g_return_val_if_fail (!cnc || GDA_IS_CONNECTION (cnc), NULL);

	if (cnc)
		gda_lockable_lock ((GdaLockable*) cnc);
	if (CLASS (provider)->get_data_handler)
		retval = CLASS (provider)->get_data_handler (provider, cnc, for_type, NULL);
	else
		retval = gda_server_provider_handler_use_default (provider, for_type);
	if (cnc)
		gda_lockable_unlock ((GdaLockable*) cnc);
	return retval;
}
