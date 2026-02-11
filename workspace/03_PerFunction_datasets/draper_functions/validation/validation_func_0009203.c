context_definition_new (const gchar        *id,
			ContextType         type,
			const gchar        *match,
			const gchar        *start,
			const gchar        *end,
			const gchar        *style,
			GSList             *context_classes,
			GtkSourceContextFlags flags,
			GError            **error)
{
	ContextDefinition *definition;
	gboolean regex_error = FALSE;
	gboolean unresolved_error = FALSE;

	g_return_val_if_fail (id != NULL, NULL);

	switch (type)
	{
		case CONTEXT_TYPE_SIMPLE:
			g_return_val_if_fail (match != NULL, NULL);
			g_return_val_if_fail (!end && !start, NULL);
			break;
		case CONTEXT_TYPE_CONTAINER:
			g_return_val_if_fail (!match, NULL);
			g_return_val_if_fail (!end || start, NULL);
			break;
	}

	definition = g_slice_new0 (ContextDefinition);

	if (match != NULL)
	{
		definition->u.match = _gtk_source_regex_new (match, G_REGEX_ANCHORED, error);

		if (definition->u.match == NULL)
		{
			regex_error = TRUE;
		}
		else if (!_gtk_source_regex_is_resolved (definition->u.match))
		{
			regex_error = TRUE;
			unresolved_error = TRUE;
			_gtk_source_regex_unref (definition->u.match);
			definition->u.match = NULL;
		}
	}

	if (start != NULL)
	{
		definition->u.start_end.start = _gtk_source_regex_new (start, G_REGEX_ANCHORED, error);

		if (definition->u.start_end.start == NULL)
		{
			regex_error = TRUE;
		}
		else if (!_gtk_source_regex_is_resolved (definition->u.start_end.start))
		{
			regex_error = TRUE;
			unresolved_error = TRUE;
			_gtk_source_regex_unref (definition->u.start_end.start);
			definition->u.start_end.start = NULL;
		}
	}

	if (end != NULL && !regex_error)
	{
		definition->u.start_end.end = _gtk_source_regex_new (end, G_REGEX_ANCHORED, error);

		if (definition->u.start_end.end == NULL)
			regex_error = TRUE;
	}

	if (unresolved_error)
	{
		g_set_error (error,
			     GTK_SOURCE_CONTEXT_ENGINE_ERROR,
			     GTK_SOURCE_CONTEXT_ENGINE_ERROR_INVALID_START_REF,
			     _("context '%s' cannot contain a \\%%{...@start} command"),
			     id);
		regex_error = TRUE;
	}

	if (regex_error)
	{
		g_slice_free (ContextDefinition, definition);
		return NULL;
	}

	definition->ref_count = 1;
	definition->id = g_strdup (id);
	definition->default_style = g_strdup (style);
	definition->type = type;
	definition->flags = flags;
	definition->children = NULL;
	definition->sub_patterns = NULL;
	definition->n_sub_patterns = 0;

	definition->context_classes = copy_context_classes (context_classes);

	return definition;
}
