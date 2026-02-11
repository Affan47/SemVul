source_view_query_tooltip_cb (GtkWidget  *widget,
                              gint        x,
                              gint        y,
                              gboolean    keyboard_mode,
                              GtkTooltip *tooltip)
{
	char            *markup = NULL, date[256];
	GiggleRevision  *revision;
	GdkRectangle     bounds;
	GtkTextIter      iter;

	gtk_text_view_window_to_buffer_coords (GTK_TEXT_VIEW (widget),
					       GTK_TEXT_WINDOW_WIDGET, x, y, &x, &y);
	gtk_text_view_get_iter_at_location (GTK_TEXT_VIEW (widget), &iter, x, y);
	gtk_text_iter_backward_chars (&iter, gtk_text_iter_get_line_offset (&iter));

	revision = source_view_get_revision_at_iter (&iter);

	if (revision) {
		const char    *committer_name = NULL;
		const char    *author_name = NULL;
		GtkAllocation  allocation;
		GiggleAuthor  *committer = NULL;
		GiggleAuthor  *author = NULL;

		gtk_widget_get_allocation (widget, &allocation);

		if (giggle_revision_get_date (revision)) {
			strftime (date, sizeof date, "%c",
				  giggle_revision_get_date (revision));
		} else {
			*date = '\0';
		}

		author = giggle_revision_get_author (revision);
		committer = giggle_revision_get_committer (revision);

		if (author)
			author_name = giggle_author_get_name (author);
		if (committer)
			committer_name = giggle_author_get_name (committer);

		markup = g_markup_printf_escaped
			("<b>%s</b> %s\n<b>%s</b> %s\n<b>%s</b> %s\n<b>%s</b> %s\n%s",
			 _("Author:"),    author_name,
			 _("Committer:"), committer_name,
			 _("Date:"),      date,
			 _("SHA:"),       giggle_revision_get_sha (revision),
			 giggle_revision_get_short_log (revision));

		gtk_text_view_get_line_yrange (GTK_TEXT_VIEW (widget),
				               &iter, &bounds.y, &bounds.height);
		gtk_text_view_buffer_to_window_coords (GTK_TEXT_VIEW (widget),
						       GTK_TEXT_WINDOW_WIDGET,
						       0, bounds.y, NULL, &bounds.y);

		bounds.x = 0;
		bounds.width = allocation.width;

		gtk_tooltip_set_tip_area (tooltip, &bounds);
		gtk_tooltip_set_markup (tooltip, markup);

		g_free (markup);

		return TRUE;
	}

	return FALSE;
}
