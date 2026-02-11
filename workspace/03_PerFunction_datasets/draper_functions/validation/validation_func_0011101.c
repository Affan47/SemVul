gtk_xtext_button_press (GtkWidget * widget, GdkEventButton * event)
{
	GtkXText *xtext = GTK_XTEXT (widget);
	GdkModifierType mask;
	textentry *ent;
	unsigned char *word;
	int line_x, x, y, offset, len;

	gdk_window_get_pointer (widget->window, &x, &y, &mask);

	if (event->button == 3 || event->button == 2)
	{
		word = gtk_xtext_get_word (xtext, x, y, 0, 0, 0, 0);
		if (word)
		{
			g_signal_emit (G_OBJECT (xtext), xtext_signals[WORD_CLICK], 0,
								word, event);
		} else
			g_signal_emit (G_OBJECT (xtext), xtext_signals[WORD_CLICK], 0,
								"", event);
		return FALSE;
	}

	if (event->button != 1)
		return FALSE;

	if (event->type == GDK_2BUTTON_PRESS)
	{
		gtk_xtext_check_mark_stamp (xtext, mask);
		if (gtk_xtext_get_word (xtext, x, y, &ent, &offset, &len, 0))
		{
			if (len == 0)
				return FALSE;
			gtk_xtext_selection_clear (xtext->buffer);
			ent->mark_start = offset;
			ent->mark_end = offset + len;
			gtk_xtext_selection_render (xtext, ent, offset, ent, offset + len);
			xtext->word_or_line_select = TRUE;
			if (prefs.hex_text_autocopy_text)
			{
				gtk_xtext_set_clip_owner (GTK_WIDGET (xtext), event);
			}
		}

		return FALSE;
	}

	if (event->type == GDK_3BUTTON_PRESS)
	{
		gtk_xtext_check_mark_stamp (xtext, mask);
		if (gtk_xtext_get_word (xtext, x, y, &ent, 0, 0, 0))
		{
			gtk_xtext_selection_clear (xtext->buffer);
			ent->mark_start = 0;
			ent->mark_end = ent->str_len;
			gtk_xtext_selection_render (xtext, ent, 0, ent, ent->str_len);
			xtext->word_or_line_select = TRUE;
			if (prefs.hex_text_autocopy_text)
			{
				gtk_xtext_set_clip_owner (GTK_WIDGET (xtext), event);
			}
		}

		return FALSE;
	}


	if (xtext->separator && xtext->buffer->indent)
	{
		line_x = xtext->buffer->indent - ((xtext->space_width + 1) / 2);
		if (line_x == x || line_x == x + 1 || line_x == x - 1)
		{
			xtext->moving_separator = TRUE;

			gtk_xtext_draw_sep (xtext, -1);
			return FALSE;
		}
	}

	xtext->button_down = TRUE;
	xtext->select_start_x = x;
	xtext->select_start_y = y;
	xtext->select_start_adj = xtext->adj->value;

	return FALSE;
}
