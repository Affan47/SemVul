stack_item_alloc(int type, size_t data_len)
{
	struct stack_item *e;

	e = calloc(1, sizeof(struct stack_item) + data_len);
	if (e == NULL)
		return NULL;

	e->data_len = data_len;
	e->type = type;

	return e;
}
