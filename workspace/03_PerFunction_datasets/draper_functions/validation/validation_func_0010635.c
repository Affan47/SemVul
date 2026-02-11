GdipIsOutlineVisiblePathPoint (GpPath *path, float x, float y, GpPen *pen, GpGraphics *graphics, BOOL *result)
{
	GpStatus status = Ok;
	cairo_surface_t* s = NULL;
	GpGraphics *g;
	GpUnit page_unit = UnitPixel;

	if (!path || !pen || !result)
		return InvalidParameter;

	if (graphics) {
		g = graphics;
		cairo_save (graphics->ct);
		page_unit = g->page_unit;
	} else {

		s = cairo_image_surface_create (CAIRO_FORMAT_A1, 1, 1);
		g = gdip_graphics_new (s);
	}

	cairo_new_path (g->ct);

	g->page_unit = UnitPixel;
	status = gdip_plot_path (g, path, FALSE);
	if (status == Ok) {

		cairo_set_antialias (g->ct, CAIRO_ANTIALIAS_NONE);
		cairo_set_line_width (g->ct, pen->width - CAIRO_AA_OFFSET_Y);
		*result = cairo_in_stroke (g->ct, x, y);
	} else {
		*result = FALSE;
	}

	if (graphics) {

		cairo_restore (graphics->ct);
		g->page_unit = page_unit;
	} else {

		cairo_surface_destroy (s);
		GdipDeleteGraphics (g);
	}

	return status;
}
