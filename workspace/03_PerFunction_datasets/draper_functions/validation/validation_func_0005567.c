l_list_remove(LList *list, void *data)
{
	LList *n;

	for (n = list; n != NULL; n = n->next) {
		if (n->data == data) {
			LList *new = l_list_remove_link(list, n);
			free(n);
			return new;
		}
	}

	return list;
}
