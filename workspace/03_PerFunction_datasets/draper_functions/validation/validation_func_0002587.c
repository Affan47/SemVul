gnome_canvas_text_draw (GnomeCanvasItem *item,
                        cairo_t *cr,
                        gint x,
                        gint y,
                        gint width,
                        gint height)
{
	GnomeCanvasText *text = GNOME_CANVAS_TEXT (item);

	if (!text->text)
		return;

	cairo_save (cr);

	if (text->clip) {
		cairo_rectangle (
			cr,
			text->clip_cx - x,
			text->clip_cy - y,
			text->clip_cwidth,
			text->clip_cheight);
		cairo_clip (cr);
	}

	cairo_set_source_rgba (
		cr,
		((text->rgba >> 24) & 0xff) / 255.0,
		((text->rgba >> 16) & 0xff) / 255.0,
		((text->rgba >>  8) & 0xff) / 255.0,
		( text->rgba        & 0xff) / 255.0);

	cairo_move_to (cr, text->cx - x, text->cy - y);
	pango_cairo_show_layout (cr, text->layout);

	cairo_restore (cr);
}
