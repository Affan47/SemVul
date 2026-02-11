_gda_mysql_meta_columns (G_GNUC_UNUSED GdaServerProvider  *prov,
			 GdaConnection      *cnc,
			 GdaMetaStore       *store,
			 GdaMetaContext     *context,
			 GError            **error,
			 G_GNUC_UNUSED const GValue       *table_catalog,
			 const GValue       *table_schema,
			 const GValue       *table_name)
{
	GdaDataModel *model, *proxy;
	gboolean retval;

	GdaMysqlReuseable *rdata;
	rdata = GDA_MYSQL_GET_REUSEABLE_DATA (gda_connection_internal_get_provider_data_error (cnc, error));
	if (!rdata)
		return FALSE;
	if ((rdata->version_long == 0) && ! _gda_mysql_compute_version (cnc, rdata, error))
		return FALSE;
	if (rdata->version_long < 50000) {
		g_set_error (error, GDA_SERVER_PROVIDER_ERROR, GDA_SERVER_PROVIDER_SERVER_VERSION_ERROR,
			     "%s", _("Mysql version 5.0 at least is required"));
		return FALSE;
	}


	if (!gda_holder_set_value (gda_set_get_holder (i_set, "schema"), table_schema, error))
		return FALSE;
	if (!gda_holder_set_value (gda_set_get_holder (i_set, "name"), table_name, error))
		return FALSE;

	model = gda_connection_statement_execute_select_full (cnc,
							      internal_stmt[I_STMT_COLUMNS_OF_TABLE],
							      i_set,
							      GDA_STATEMENT_MODEL_RANDOM_ACCESS,
							      _col_types_columns, error);
	if (model == NULL)
		retval = FALSE;
	else {
		proxy = (GdaDataModel *) gda_data_proxy_new (model);
		gda_data_proxy_set_sample_size ((GdaDataProxy *) proxy, 0);
		gint n_rows = gda_data_model_get_n_rows (model);
		gint i;
		for (i = 0; i < n_rows; ++i) {
			const GValue *value1, *value2 = NULL;
			value1 = gda_data_model_get_value_at (model, 7, i, error);
			if (value1)
				value2 = gda_data_model_get_value_at (model, 10, i, error);
			if (!value1 || !value2) {
				retval = FALSE;
				break;
			}

			GValue *newvalue = map_mysql_type_to_gda (value1, (const char*)value2);

			retval = gda_data_model_set_value_at (GDA_DATA_MODEL(proxy), 9, i, newvalue, error);
			gda_value_free (newvalue);
			if (!retval)
				break;
		}

		if (retval) {
			gda_meta_store_set_reserved_keywords_func (store,
								   _gda_mysql_reuseable_get_reserved_keywords_func
								   ((GdaProviderReuseable*) rdata));
			retval = gda_meta_store_modify (store, context->table_name, proxy,
							"table_schema=##schema::string AND table_name=##name::string",
							error,
							"schema", table_schema, "name", table_name, NULL);
		}
		g_object_unref (G_OBJECT(proxy));
		g_object_unref (G_OBJECT(model));
	}

	return retval;
}
