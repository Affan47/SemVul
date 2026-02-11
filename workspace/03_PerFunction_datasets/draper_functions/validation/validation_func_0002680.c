brasero_file_node_sort_children (BraseroFileNode *parent,
				 GCompareFunc sort_func)
{
	BraseroFileNode *new_order = NULL;
	BraseroFileNode *iter;
	BraseroFileNode *next;
	gint *array = NULL;
	gint num_children;
	guint oldpos = 1;
	guint newpos;


	if (parent->is_hidden)
		return NULL;

	new_order = BRASERO_FILE_NODE_CHILDREN (parent);
	if (!new_order)
		return NULL;

	if (!new_order->next)
		return NULL;


	num_children = brasero_file_node_get_n_children (parent);
	array = g_new (gint, num_children);

	next = new_order->next;
	new_order->next = NULL;
	array [0] = 0;

	for (iter = next; iter; iter = next, oldpos ++) {

		next = iter->next;
		iter->next = NULL;

		newpos = 0;
		new_order = brasero_file_node_insert (new_order,
						      iter,
						      sort_func,
						      &newpos);

		if (newpos < oldpos)
			memmove (array + newpos + 1, array + newpos, (oldpos - newpos) * sizeof (guint));

		array [newpos] = oldpos;
	}


	parent->union2.children = new_order;

	return array;
}
