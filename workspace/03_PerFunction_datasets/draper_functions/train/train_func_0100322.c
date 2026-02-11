gsql_source_editor_property_set (gpointer src)
{
	GSQL_TRACE_FUNC;

	GtkWidget *source = src;

	PangoFontDescription * font_desc;
	gchar * conf_string;
	gboolean conf_boolean;
	gint conf_int;

	conf_boolean = gsql_conf_value_get_boolean (GSQL_CONF_EDITOR_USE_SYSTEM_FONT);

	if (conf_boolean)
		conf_string = gsql_conf_value_get_string_at_root (GNOME_SYSTEM_FONT);
	else
		conf_string = gsql_conf_value_get_string (GSQL_CONF_EDITOR_FONT_NAME);

	if (!conf_string)
		conf_string = gsql_conf_value_get_string_at_root (GNOME_SYSTEM_FONT);

	font_desc = pango_font_description_from_string (conf_string);
	gtk_widget_modify_font (GTK_WIDGET (source), font_desc);

	conf_string = gsql_conf_value_get_string (GSQL_CONF_EDITOR_COLOR_SCHEME);

	if (conf_string)
	{
		GtkSourceBuffer *buff = GTK_SOURCE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (src)));
		GtkSourceStyleSchemeManager* manager = gtk_source_style_scheme_manager_get_default();
		GtkSourceStyleScheme* scheme = gtk_source_style_scheme_manager_get_scheme (manager,
																				   conf_string);
		gtk_source_buffer_set_style_scheme (buff, scheme);
	}

	conf_boolean = gsql_conf_value_get_boolean (GSQL_CONF_EDITOR_HIGHLIGHT_LINE);
	gtk_source_view_set_highlight_current_line (GTK_SOURCE_VIEW (source),
												conf_boolean);

	conf_boolean = gsql_conf_value_get_boolean (GSQL_CONF_EDITOR_SHOW_LINE_NUM);

	gtk_source_view_set_show_line_numbers (GTK_SOURCE_VIEW (source),
											conf_boolean);

	conf_boolean = gsql_conf_value_get_boolean (GSQL_CONF_EDITOR_WRAPPING);

	if (conf_boolean)
		gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (source),GTK_WRAP_WORD);
	else
		gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (source),GTK_WRAP_NONE);

	conf_boolean = gsql_conf_value_get_boolean (GSQL_CONF_EDITOR_USE_SPACE);

	gtk_source_view_set_insert_spaces_instead_of_tabs (GTK_SOURCE_VIEW (source),
														conf_boolean);

	conf_int = gsql_conf_value_get_int (GSQL_CONF_EDITOR_TAB_WIDTH);

	if ((conf_int <= 0) || (conf_int > 8))
		conf_int = GSQL_CONF_EDITOR_TAB_WIDTH_DEFAULT;

	gtk_source_view_set_tab_width (GTK_SOURCE_VIEW (source), conf_int);

	conf_boolean = gsql_conf_value_get_boolean (GSQL_CONF_EDITOR_AUTO_INDENT);
	gtk_source_view_set_auto_indent (GTK_SOURCE_VIEW (source), conf_boolean);

}
