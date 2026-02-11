isl_tab_get_sample_value(struct isl_tab *tab)
{
	int i;
	struct isl_vec *vec;
	isl_int m;

	if (!tab)
		return NULL;

	vec = isl_vec_alloc(tab->mat->ctx, 1 + tab->n_var);
	if (!vec)
		return NULL;

	isl_int_init(m);

	isl_int_set_si(vec->block.data[0], 1);
	for (i = 0; i < tab->n_var; ++i) {
		int row;
		if (!tab->var[i].is_row) {
			isl_int_set_si(vec->block.data[1 + i], 0);
			continue;
		}
		row = tab->var[i].index;
		isl_int_gcd(m, vec->block.data[0], tab->mat->row[row][0]);
		isl_int_divexact(m, tab->mat->row[row][0], m);
		isl_seq_scale(vec->block.data, vec->block.data, m, 1 + i);
		isl_int_divexact(m, vec->block.data[0], tab->mat->row[row][0]);
		isl_int_mul(vec->block.data[1 + i], m, tab->mat->row[row][1]);
	}
	vec = isl_vec_normalize(vec);

	isl_int_clear(m);
	return vec;
}
