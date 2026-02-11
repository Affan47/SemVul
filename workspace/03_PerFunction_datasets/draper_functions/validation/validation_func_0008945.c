gtk_source_completion_model_add_proposals (GtkSourceCompletionModel    *model,
					   GtkSourceCompletionProvider *provider,
					   GList                       *proposals)
{
	GList *provider_node = NULL;

	g_return_if_fail (GTK_SOURCE_IS_COMPLETION_MODEL (model));
	g_return_if_fail (GTK_SOURCE_IS_COMPLETION_PROVIDER (provider));

	if (proposals == NULL)
	{
		return;
	}

	provider_node = get_provider_node (model, provider);

	if (provider_node == NULL)
	{
		provider_node = create_provider_info (model, provider);
	}

	g_list_foreach (proposals, (GFunc)add_proposal, provider_node);
}
