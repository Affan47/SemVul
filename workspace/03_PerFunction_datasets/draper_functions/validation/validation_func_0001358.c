clipboard_copy_range (Sheet *sheet, GnmRange const *r)
{
	GnmCellRegion *cr;
	GSList *merged, *ptr;
	GSList *objects;

	g_return_val_if_fail (IS_SHEET (sheet), NULL);
	g_return_val_if_fail (range_is_sane (r), NULL);

	cr = gnm_cell_region_new (sheet);
	cr->base = r->start;
	cr->cols = range_width (r);
	cr->rows = range_height (r);
	cr->col_state = colrow_get_states (sheet,
		TRUE,  r->start.col, r->end.col);
	cr->row_state = colrow_get_states (sheet,
		FALSE, r->start.row, r->end.row);

	sheet_foreach_cell_in_range ( sheet, CELL_ITER_IGNORE_NONEXISTENT,
		r->start.col, r->start.row,
		r->end.col, r->end.row,
		(CellIterFunc) cb_clipboard_prepend_cell, cr);
	objects = sheet_objects_get (sheet, r, G_TYPE_NONE);
	g_slist_foreach (objects, (GFunc)cb_dup_objects, cr);
	g_slist_free (objects);

	cr->styles = sheet_style_get_range (sheet, r);

	merged = gnm_sheet_merge_get_overlap (sheet, r);
	for (ptr = merged ; ptr != NULL ; ptr = ptr->next) {
		GnmRange *tmp = gnm_range_dup (ptr->data);
		range_translate (tmp, sheet, -r->start.col, -r->start.row);
		cr->merged = g_slist_prepend (cr->merged, tmp);
	}
	g_slist_free (merged);

	return cr;
}
