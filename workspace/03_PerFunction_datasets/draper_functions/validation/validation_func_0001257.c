plugin_db_catalog_update ( GWDBContext *context, GWDBCatalog *catalog) {
	GWDBCatalog *catalog_dup = NULL;
	_data *data = NULL;


	if ( context != NULL && catalog != NULL ) {
		data = gw_db_context_get_data ( context);

		catalog_dup = data->catalog;
		if ( !gw_db_catalog_equals ( catalog_dup, catalog) ) {
			gw_db_catalog_dup ( catalog, &catalog_dup);
			gw_db_catalog_set_ismodified ( catalog_dup, TRUE);

			return 0;
		} else {}
	}

	return -1;
}
