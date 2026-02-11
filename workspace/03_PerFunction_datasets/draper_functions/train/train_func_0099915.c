fz_free_display_list(fz_context *ctx, fz_display_list *list)
{
	fz_display_node *node;

	if (list == NULL)
		return;
	node = list->first;
	while (node)
	{
		fz_display_node *next = node->next;
		fz_free_display_node(ctx, node);
		node = next;
	}
	fz_free(ctx, list);
}
