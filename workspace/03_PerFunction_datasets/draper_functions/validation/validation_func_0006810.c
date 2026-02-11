tagged_token_list_get_all (GList *list)
{
	GList *tokens = NULL;

	for (; list != NULL; list = g_list_next (list))
	{
		tokens = g_list_concat (tokens, g_list_copy (((TaggedTokenItem *)list->data)->tokens));
	}

	return tokens;
}
