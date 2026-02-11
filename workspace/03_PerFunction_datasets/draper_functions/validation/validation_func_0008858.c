gda_vconnection_data_model_remove (GdaVconnectionDataModel *cnc, const gchar *table_name, GError **error)
{
	GdaVConnectionTableData *td;

	g_return_val_if_fail (GDA_IS_VCONNECTION_DATA_MODEL (cnc), FALSE);
	g_return_val_if_fail (table_name && *table_name, FALSE);

	td = _gda_vconnection_get_table_data_by_name (cnc, table_name);
	if (!td) {
		g_set_error (error, GDA_SERVER_PROVIDER_ERROR,
			     GDA_SERVER_PROVIDER_MISUSE_ERROR,
			     "%s", _("Table to remove not found"));
		return FALSE;
	}

	return get_rid_of_vtable (cnc, td, FALSE, error);
}
