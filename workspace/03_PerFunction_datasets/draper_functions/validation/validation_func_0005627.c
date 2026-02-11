get_css_color_style (GtkSourceStyle *style,
                     gchar         **bg,
                     gchar         **text)
{
	GdkRGBA color;

	if (get_color (style, FALSE, &color))
	{
		gchar *bg_color;
		bg_color = gdk_rgba_to_string (&color);
		*bg = g_strdup_printf ("%s: %s;\n", "background-color", bg_color);
		g_free (bg_color);
	}
	else
	{
		*bg = NULL;
	}

	if (get_color (style, TRUE, &color))
	{
		gchar *text_color;
		text_color = gdk_rgba_to_string (&color);
		*text = g_strdup_printf ("%s: %s;\n", "color", text_color);
		g_free (text_color);
	}
	else
	{
		*text = NULL;
	}
}
