gnome_canvas_text_set_markup (GnomeCanvasText *textitem,
                              const gchar *markup)
{
	PangoAttrList *attr_list = NULL;
	gchar         *text = NULL;
	GError        *error = NULL;

	if (markup && !pango_parse_markup (markup, -1,
					   0,
					   &attr_list, &text, NULL,
					   &error))
	{
		g_warning (
			"Failed to set cell text from markup due to "
			"error parsing markup: %s", error->message);
		g_error_free (error);
		return;
	}

	g_free (textitem->text);
	if (textitem->attr_list)
		pango_attr_list_unref (textitem->attr_list);

	textitem->text = text;
	textitem->attr_list = attr_list;

	pango_layout_set_text (textitem->layout, text, -1);

	gnome_canvas_text_apply_attributes (textitem);
}
