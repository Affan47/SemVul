goc_rectangle_update_bounds (GocItem *item)
{
	cairo_surface_t *surface;
	cairo_t *cr;

	surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 1 , 1);
	cr = cairo_create (surface);

	cairo_save (cr);
	if (goc_rectangle_prepare_draw (item, cr, 0)) {
		cairo_restore (cr);
		if (go_styled_object_set_cairo_line (GO_STYLED_OBJECT (item), cr))
			cairo_stroke_extents (cr, &item->x0, &item->y0, &item->x1, &item->y1);
		else if (go_style_is_fill_visible (go_styled_object_get_style (GO_STYLED_OBJECT (item))))
			cairo_fill_extents (cr, &item->x0, &item->y0, &item->x1, &item->y1);
		else {
			item->x0 = item->y0 = G_MAXDOUBLE;
			item->x1 = item->y1 = -G_MAXDOUBLE;
		}
	}

	cairo_destroy (cr);
	cairo_surface_destroy (surface);
}
