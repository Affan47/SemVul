totem_cmml_parse_start (TotemCmmlContext	*context,
			const xmlChar		*tag,
			const xmlChar		**attrs)
{
	g_return_if_fail (context != NULL);
	g_return_if_fail (tag != NULL);

	if (g_strcmp0 ((const gchar *) tag, "cmml") == 0) {
		if (G_UNLIKELY (context->status != TOTEM_CMML_NONE))
			return;


		if (G_UNLIKELY (xmlTextReaderIsEmptyElement (context->reader)))
			return;

		context->status = TOTEM_CMML_CMML;
	} else if (g_strcmp0 ((const gchar *) tag, "head") == 0) {
		if (G_UNLIKELY (context->status != TOTEM_CMML_CMML))
			return;


		if (G_UNLIKELY (xmlTextReaderIsEmptyElement (context->reader)))
			context->status = TOTEM_CMML_CMML;

		context->status = TOTEM_CMML_HEAD;
	} else if (g_strcmp0 ((const gchar *) tag, "clip") == 0) {
		if (G_UNLIKELY (context->status != TOTEM_CMML_CMML))
			return;

		context->clip = totem_cmml_clip_new_from_attrs (attrs);


		if (G_UNLIKELY (xmlTextReaderIsEmptyElement (context->reader))) {
			if (G_LIKELY(context->callback != NULL))
				(context->callback) (context->clip, context->user_data);

			context->status = TOTEM_CMML_CMML;
			totem_cmml_clip_free (context->clip);
			context->clip = NULL;
		} else
			context->status = TOTEM_CMML_CLIP;
	} else if (g_strcmp0 ((const gchar *) tag, "img") == 0) {
		if (G_UNLIKELY (context->status != TOTEM_CMML_CLIP))
			return;

		totem_cmml_clip_insert_img_attr (context->clip, attrs);
	}
}
