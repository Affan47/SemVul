string_list_print(FILE* outfile, StringList* list, int flag)
{
	struct string_node* node;

	node = list->head;

	while(node != NULL)
	{
		if (node->flag & flag)
			fprintf(outfile,"%s\n", node->string);
		node = node->next;
	}
}
