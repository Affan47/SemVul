wb_view_style_feedback (WorkbookView *wbv)
{
	SheetView *sv;
	GnmStyle const *style;
	GnmSheetSlicer const *dslicer;
	GODataSlicerField *dsfield;
	GnmValidation const *val;
	GOFormat const *fmt_style, *fmt_cell;
	GnmCell *cell;
	gboolean update_controls = TRUE;

	g_return_if_fail (IS_WORKBOOK_VIEW (wbv));

	sv = wbv->current_sheet_view;
	if (sv == NULL)
		return;

	style = sheet_style_get (sv->sheet,
		sv->edit_pos.col, sv->edit_pos.row);
	fmt_style = gnm_style_get_format (style);
	if (go_format_is_general (fmt_style) &&
	    (cell = sheet_cell_get (sv->sheet, sv->edit_pos.col, sv->edit_pos.row)) &&
	    cell->value && VALUE_FMT (cell->value))
		fmt_cell = VALUE_FMT (cell->value);
	else
		fmt_cell = fmt_style;

	if (go_format_eq (fmt_cell, fmt_style)) {
		if (style == wbv->current_style)
			update_controls = FALSE;
		gnm_style_ref (style);
	} else {
		GnmStyle *tmp = gnm_style_dup (style);
		gnm_style_set_format (tmp, fmt_cell);
		style = tmp;
	}

	if (wbv->current_style != NULL)
		gnm_style_unref (wbv->current_style);
	wbv->current_style = style;

	if (wbv->in_cell_combo != NULL) {
		sheet_object_clear_sheet (wbv->in_cell_combo);
		g_object_unref (wbv->in_cell_combo);
		wbv->in_cell_combo = NULL;
	}

	if (gnm_style_is_element_set (style, MSTYLE_VALIDATION) &&
	    NULL != (val = gnm_style_get_validation (style)) &&
	    val->type == GNM_VALIDATION_TYPE_IN_LIST &&
	    val->use_dropdown)
		wbv->in_cell_combo = gnm_validation_combo_new (val, sv);
	else if (NULL != (dslicer = gnm_sheet_slicers_at_pos (sv->sheet, &sv->edit_pos)) &&
		   NULL != (dsfield = gnm_sheet_slicer_field_header_at_pos (dslicer, &sv->edit_pos)))
		wbv->in_cell_combo = g_object_new (gnm_sheet_slicer_combo_get_type (),
						   "sheet-view", sv,
						   "field",	 dsfield,
						   NULL);

	if (NULL != wbv->in_cell_combo)
	{
		const double a_offsets [4] = { 0., 0., 1., 1. };
		SheetObjectAnchor  anchor;
		GnmRange corner;
		GnmRange const *r;
		if (NULL == (r = gnm_sheet_merge_contains_pos (sv->sheet, &sv->edit_pos)))
			r = range_init_cellpos (&corner, &sv->edit_pos);
		sheet_object_anchor_init (&anchor, r, a_offsets, GOD_ANCHOR_DIR_DOWN_RIGHT);
		sheet_object_set_anchor (wbv->in_cell_combo, &anchor);
		sheet_object_set_sheet (wbv->in_cell_combo, sv->sheet);
	}

	if (update_controls) {
		WORKBOOK_VIEW_FOREACH_CONTROL(wbv, control,
			wb_control_style_feedback (control, NULL););
	}
}
