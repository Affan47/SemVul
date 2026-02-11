draw_downward_diagonal_hatch (cairo_surface_t *hatch, GpHatch *hbr)
{
	double hatch_size = gdip_hatch_get_width (hbr);
	double line_width = gdip_hatch_get_line_width (hbr);

	cairo_t *ct2 = create_hatch_context (hatch, CAIRO_LINE_CAP_SQUARE, FALSE);
	if (ct2 == NULL)
		return CAIRO_STATUS_NO_MEMORY;

	draw_background (ct2, hbr->backColor, hatch_size, hatch_size);

	set_color (ct2, hbr->foreColor);
	cairo_set_line_width (ct2, line_width);
	cairo_move_to (ct2, CAIRO_AA_OFFSET_X, hatch_size / 2.0 + CAIRO_AA_OFFSET_Y);
	cairo_line_to (ct2, hatch_size / 2.0 + CAIRO_AA_OFFSET_X, hatch_size + CAIRO_AA_OFFSET_Y);
	cairo_move_to (ct2, hatch_size / 2.0 + CAIRO_AA_OFFSET_X, CAIRO_AA_OFFSET_Y);
	cairo_line_to (ct2, hatch_size + CAIRO_AA_OFFSET_X, hatch_size / 2.0 + CAIRO_AA_OFFSET_Y);
	cairo_stroke (ct2);

	cairo_destroy (ct2);
	return CAIRO_STATUS_SUCCESS;
}
