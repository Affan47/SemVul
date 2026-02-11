mime_list_equal (GList *a, GList *b)
{
	while (a && b) {
		if (strcmp (a->data, b->data)) {
			return FALSE;
		}
		a = a->next;
		b = b->next;
	}

	return (a == b);
}
