append_inner_node_end(struct llist *result,
		struct rnode *current)
{
	if (! append_element(result, strdup(")")))
		return FAILURE;
	if (strcmp("", current->label) != 0)
		if (! append_element(result, strdup(current->label)))
			return FAILURE;
	if (show_addresses)
		if (! append_element( result, masprintf("@%p", current)))
			return FAILURE;
	if (strcmp("", current->edge_length_as_string) != 0) {
		if (! append_element(result, strdup(":")))
			return FAILURE;
		if (! append_element(result,
				strdup(current->edge_length_as_string)))
			return FAILURE;
	}
	current->seen = 0;

	return SUCCESS;
}
