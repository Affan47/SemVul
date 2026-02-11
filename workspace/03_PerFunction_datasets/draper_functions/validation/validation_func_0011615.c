render_offsets (GtkHex *gh,
                cairo_t *cr,
                gint imin,
                gint imax)
{
	GtkWidget *w = gh->offsets;
	GdkRGBA bg_color;
	GdkRGBA fg_color;
	GtkAllocation allocation;
	GtkStateFlags state;
	GtkStyleContext *context;
	gint i;
	gchar offstr[9];

	if(!gtk_widget_get_realized(GTK_WIDGET(gh)))
		return;

	context = gtk_widget_get_style_context (w);
	state = gtk_widget_get_state_flags (w);

	gtk_style_context_get_background_color (context, state, &bg_color);
	gtk_style_context_get_color (context, state, &fg_color);

	gtk_widget_get_allocation(w, &allocation);
	gdk_cairo_set_source_rgba (cr, &bg_color);
	cairo_rectangle (cr, 0, imin * gh->char_height, allocation.width, (imax - imin + 1) * gh->char_height);
	cairo_fill (cr);

	imax = MIN(imax, gh->vis_lines);
	imax = MIN(imax, gh->lines - gh->top_line - 1);

	gdk_cairo_set_source_rgba (cr, &fg_color);

	for(i = imin; i <= imax; i++) {
		sprintf(offstr, "%08X", (gh->top_line + i)*gh->cpl + gh->starting_offset);
		cairo_move_to (cr, 0, i * gh->char_height);
		pango_layout_set_text (gh->olayout, offstr, 8);
		pango_cairo_show_layout (cr, gh->olayout);
	}
}
