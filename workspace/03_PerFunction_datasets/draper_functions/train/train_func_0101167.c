insert_dname_into_table(hattrie_t *table, knot_dname_t *d,
                                   dummy_node_t **n)
{
	int d_size = knot_dname_size(d);
	if (d_size < 0) {
		return KNOT_EINVAL;
	}

	value_t *val = hattrie_tryget(table, (char *)d, d_size);
	if (val == NULL) {

		*n = xmalloc(sizeof(dummy_node_t));
		init_list(&(*n)->node_list);
		*hattrie_get(table, (char *)d, d_size) = *n;
		return 0;
	} else {

		*n = (dummy_node_t *)(*val);
		return 1;
	}
}
