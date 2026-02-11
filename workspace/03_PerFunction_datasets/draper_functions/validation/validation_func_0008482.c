snippet_new (const gchar* trigger_key,
             GList* snippet_languages,
             const gchar* snippet_name,
             const gchar* snippet_content,
             GList* variable_names,
             GList* variable_default_values,
             GList* variable_globals,
             GList* keywords)
{
	AnjutaSnippet* snippet = NULL;
	GList *iter1 = NULL, *iter2 = NULL, *iter3 = NULL;
	gchar* temporary_string_holder = NULL;
	AnjutaSnippetVariable* cur_snippet_var = NULL;


	g_return_val_if_fail (trigger_key != NULL, NULL);
	g_return_val_if_fail (snippet_name != NULL, NULL);
	g_return_val_if_fail (snippet_content != NULL, NULL);
	g_return_val_if_fail (g_list_length (variable_names) == g_list_length (variable_default_values),
	                      NULL);
	g_return_val_if_fail (g_list_length (variable_names) == g_list_length (variable_globals),
	                      NULL);


	snippet = ANJUTA_SNIPPET (g_object_new (snippet_get_type (), NULL));


	snippet->priv->trigger_key      = g_strdup (trigger_key);
	snippet->priv->snippet_name     = g_strdup (snippet_name);
	snippet->priv->snippet_content  = g_strdup (snippet_content);


	snippet->priv->snippet_languages = NULL;
	for (iter1 = g_list_first (snippet_languages); iter1 != NULL; iter1 = g_list_next (iter1))
	{
		temporary_string_holder = g_strdup ((const gchar *)iter1->data);
		snippet->priv->snippet_languages = g_list_append (snippet->priv->snippet_languages,
		                                                  temporary_string_holder);
	}


	snippet->priv->keywords = NULL;
	for (iter1 = g_list_first (keywords); iter1 != NULL; iter1 = g_list_next (iter1))
	{
		temporary_string_holder = g_strdup ((gchar *)iter1->data);
		snippet->priv->keywords = g_list_append (snippet->priv->keywords, temporary_string_holder);
	}


	snippet->priv->variables = NULL;
	iter1 = g_list_first (variable_names);
	iter2 = g_list_first (variable_default_values);
	iter3 = g_list_first (variable_globals);
	while (iter1 != NULL && iter2 != NULL && iter3 != NULL)
	{
		cur_snippet_var = g_malloc (sizeof (AnjutaSnippetVariable));

		cur_snippet_var->variable_name = g_strdup ((gchar*)iter1->data);
		cur_snippet_var->default_value = g_strdup ((gchar*)iter2->data);
		cur_snippet_var->is_global = GPOINTER_TO_INT (iter3->data);

		cur_snippet_var->cur_value_len = 0;
		cur_snippet_var->relative_positions = g_ptr_array_new ();

		snippet->priv->variables = g_list_append (snippet->priv->variables, cur_snippet_var);

		iter1 = g_list_next (iter1);
		iter2 = g_list_next (iter2);
		iter3 = g_list_next (iter3);
	}
	DEBUG_PRINT ("Snippet %s created.\n", snippet_name);
	return snippet;
}
