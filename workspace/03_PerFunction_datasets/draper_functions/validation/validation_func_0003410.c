cb_cut_into_rows (gpointer data, gpointer user_data)
{
	GnmValue *range = (GnmValue *)data;
	GnmValue *row_value;
	GSList **list_of_units = (GSList **) user_data;
	gint row;

	if (range == NULL) {
		return;
	}
	if ((range->type != VALUE_CELLRANGE) ||
	    (range->v_range.cell.b.sheet != NULL &&
	     range->v_range.cell.b.sheet != range->v_range.cell.a.sheet)) {
		value_release (range);
		return;
	}

	cb_adjust_areas (data, NULL);

	if (range->v_range.cell.a.row == range->v_range.cell.b.row) {
		*list_of_units = g_slist_prepend (*list_of_units, range);
		return;
	}

	for (row = range->v_range.cell.a.row; row <= range->v_range.cell.b.row; row++) {
		row_value = value_dup (range);
		row_value->v_range.cell.a.row = row;
		row_value->v_range.cell.b.row = row;
		*list_of_units = g_slist_prepend (*list_of_units, row_value);
	}
	value_release (range);
	return;
}
