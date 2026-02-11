isl_tab_init_samples(struct isl_tab *tab)
{
	if (!tab)
		return NULL;

	tab->n_sample = 0;
	tab->n_outside = 0;
	tab->samples = isl_mat_alloc(tab->mat->ctx, 1, 1 + tab->n_var);
	if (!tab->samples)
		goto error;
	tab->sample_index = isl_alloc_array(tab->mat->ctx, int, 1);
	if (!tab->sample_index)
		goto error;
	return tab;
error:
	isl_tab_free(tab);
	return NULL;
}
