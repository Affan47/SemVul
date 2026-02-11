etgl_key_press (GObject *object,
                gint row,
                gint col,
                GdkEvent *event,
                ETableGroupLeaf *etgl)
{
	ETableSubset *table_subset;
	gint model_row;

	table_subset = E_TABLE_SUBSET (etgl->ets);
	model_row = e_table_subset_view_to_model_row (table_subset, row);

	if (model_row < 0)
		return FALSE;

	return e_table_group_key_press (
		E_TABLE_GROUP (etgl), model_row, col, event);
}
