l2tp_dict_find_attr_by_id(int id)
{
	struct l2tp_dict_attr_t *attr;

	list_for_each_entry(attr, &dict->items, entry) {
		if (attr->id == id)
			return attr;
	}

	return NULL;
}
