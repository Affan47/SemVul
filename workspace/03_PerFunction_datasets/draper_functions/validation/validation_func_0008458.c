_gda_web_meta_udt (G_GNUC_UNUSED GdaServerProvider *prov, GdaConnection *cnc,
		   GdaMetaStore *store, GdaMetaContext *context, GError **error,
		   const GValue *udt_catalog, const GValue *udt_schema)
{
	WebConnectionData *cdata;

	cdata = (WebConnectionData*) gda_connection_internal_get_provider_data_error (cnc, error);
	if (!cdata)
		return FALSE;


	if (cdata->reuseable) {
		if (cdata->reuseable->operations->re_meta_funcs.udt)
			return cdata->reuseable->operations->re_meta_funcs.udt (NULL, cnc, store,
										context, error, udt_catalog,
										udt_schema);
		else
			return TRUE;
	}


	return TRUE;
}
