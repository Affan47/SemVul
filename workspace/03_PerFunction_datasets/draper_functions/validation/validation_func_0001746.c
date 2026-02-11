cb_adjust_areas (gpointer data, G_GNUC_UNUSED gpointer user_data)
{
	GnmValue *range = (GnmValue *)data;

	if (range == NULL || (range->type != VALUE_CELLRANGE)) {
		return;
	}

	range->v_range.cell.a.col_relative = 0;
	range->v_range.cell.a.row_relative = 0;
	range->v_range.cell.b.col_relative = 0;
	range->v_range.cell.b.row_relative = 0;
}
