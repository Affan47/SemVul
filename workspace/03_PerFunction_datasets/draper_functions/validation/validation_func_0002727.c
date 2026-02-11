index_mm_searchwild_allvalues(struct index_mm_node *node,
						struct index_value **out)
{
	struct index_mm_value *itr, *itr_end;

	itr = node->values.values;
	itr_end = itr + node->values.len;
	for (; itr < itr_end; itr++)
		add_value(out, itr->value, itr->len, itr->priority);

	index_mm_free_node(node);
}
