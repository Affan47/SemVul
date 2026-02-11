snippet_get_variable_globals_list (AnjutaSnippet* snippet)
{
	GList *iter = NULL;
	GList *variable_globals = NULL;
	gboolean temp_holder = FALSE;
	AnjutaSnippetVariable *cur_snippet_var = NULL;


	g_return_val_if_fail (ANJUTA_IS_SNIPPET (snippet), NULL);

	for (iter = g_list_first (snippet->priv->variables); iter != NULL; iter = g_list_next (iter))
	{
		cur_snippet_var = (AnjutaSnippetVariable *)iter->data;
		temp_holder = cur_snippet_var->is_global;
		variable_globals = g_list_append (variable_globals, GINT_TO_POINTER (temp_holder));
	}

	return variable_globals;
}
