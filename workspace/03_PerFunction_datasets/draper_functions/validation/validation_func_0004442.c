add_to_list(FILE_LIST** list, const char* file)
{
	if (*list == NULL) {
		*list = alloc_node(file);

		if (*list == NULL)
			return -1;
	}
	else {
		FILE_LIST* node = *list;

		while (node->next_file != NULL)
			node = node->next_file;

		node->next_file = alloc_node(file);

		if (node->next_file == NULL)
			return -1;
	}

	return 0;
}
