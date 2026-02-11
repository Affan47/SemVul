value_to_list(struct grecs_value *val)
{
	struct grecs_list *list;
	int i;

	if (val->type == GRECS_TYPE_LIST)
		return;
	list = grecs_value_list_create();
	switch (val->type) {
	case GRECS_TYPE_STRING:
		grecs_list_append(list, grecs_value_ptr_from_static(val));
		break;

	case GRECS_TYPE_ARRAY:
		for (i = 0; i < val->v.arg.c; i++)
			grecs_list_append(list, val->v.arg.v[i]);
	}
	val->type = GRECS_TYPE_LIST;
	val->v.list = list;
}
