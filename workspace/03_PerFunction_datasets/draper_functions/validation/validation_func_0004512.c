murrine_begin_paint (GdkDrawable *window, GdkRectangle *area)
{
	cairo_t *cr;

	g_return_val_if_fail (window != NULL, NULL);

	cr = (cairo_t*) gdk_cairo_create (window);
	cairo_set_line_width (cr, 1.0);

	if (area)
	{
		cairo_rectangle (cr, area->x, area->y, area->width, area->height);
		cairo_clip_preserve (cr);
		cairo_new_path (cr);
	}

	return cr;
}
