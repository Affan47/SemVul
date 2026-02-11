gda_thread_provider_statement_prepare (GdaServerProvider *provider, GdaConnection *cnc,
				       GdaStatement *stmt, GError **error)
{
	ThreadConnectionData *cdata;
	PrepareStatementData wdata;
	gpointer res;
	guint jid;

	g_return_val_if_fail (GDA_IS_CONNECTION (cnc), FALSE);
	g_return_val_if_fail (gda_connection_get_provider (cnc) == provider, FALSE);
	g_return_val_if_fail (GDA_IS_STATEMENT (stmt), FALSE);

	cdata = (ThreadConnectionData*) gda_connection_internal_get_provider_data_error (cnc, error);
	if (!cdata)
		return FALSE;

	wdata.prov = cdata->cnc_provider;
	wdata.cnc = cdata->sub_connection;
	wdata.stmt = stmt;

	jid = gda_thread_wrapper_execute (cdata->wrapper,
					  (GdaThreadWrapperFunc) sub_thread_prepare_statement, &wdata, NULL, NULL);
	res = gda_thread_wrapper_fetch_result (cdata->wrapper, TRUE, jid, error);
	return GPOINTER_TO_INT (res) ? TRUE : FALSE;
}
