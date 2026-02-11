gnm_style_get_font (GnmStyle const *style, PangoContext *context)
{
	g_return_val_if_fail (style != NULL, NULL);

	if (!style->font || style->font_context != context) {
		char const *name;
		gboolean bold, italic;
		double size;

		gnm_style_clear_font ((GnmStyle *)style);

		if (elem_is_set (style, MSTYLE_FONT_NAME))
			name = gnm_style_get_font_name (style);
		else
			name = DEFAULT_FONT;

		if (elem_is_set (style, MSTYLE_FONT_BOLD))
			bold = gnm_style_get_font_bold (style);
		else
			bold = FALSE;

		if (elem_is_set (style, MSTYLE_FONT_ITALIC))
			italic = gnm_style_get_font_italic (style);
		else
			italic = FALSE;

		if (elem_is_set (style, MSTYLE_FONT_SIZE))
			size = gnm_style_get_font_size (style);
		else
			size = DEFAULT_SIZE;

		((GnmStyle *)style)->font =
			gnm_font_new (context, name, size, bold, italic);
		((GnmStyle *)style)->font_context = g_object_ref (context);
	}

	return style->font;
}
