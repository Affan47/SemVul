x_list_concat (x_list_t *list1, x_list_t *list2)
{
	x_list_t *tmp_list;

	if (list2) {
		tmp_list = x_list_last (list1);
		if (tmp_list) {
			tmp_list->next = list2;
		} else {
			list1 = list2;
		}
		list2->prev = tmp_list;
	}

	return list1;
}
