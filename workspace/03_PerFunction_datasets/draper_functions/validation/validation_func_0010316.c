filter_preset_status_set(Filter *flt, gint status)
{
Category *catitem;
GList *list;


	flt->status = status;
	flt->option[FILTER_STATUS] = 0;
	flt->reconciled = TRUE;
	flt->reminded = TRUE;
	flt->forceadd = FALSE;
	flt->forcechg = FALSE;

	flt->option[FILTER_CATEGORY] = 0;
	list = g_hash_table_get_values(GLOBALS->h_cat);
	while (list != NULL)
	{
		catitem = list->data;
		catitem->filter = FALSE;
		list = g_list_next(list);
	}
	g_list_free(list);

	switch( status )
	{
		case FLT_STATUS_UNCATEGORIZED:
			flt->option[FILTER_CATEGORY] = 1;
			catitem = da_cat_get(0);
			catitem->filter = TRUE;
			break;

		case FLT_STATUS_UNRECONCILED:
			flt->option[FILTER_STATUS] = 2;
			flt->reconciled = TRUE;
			break;
	}

}
