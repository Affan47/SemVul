get_union_pw_aff(__isl_take isl_pw_multi_aff *pma, void *user)
{
	struct isl_union_pw_multi_aff_get_union_pw_aff_data *data = user;
	int n_out;
	isl_pw_aff *pa;

	if (!pma)
		return -1;

	n_out = isl_pw_multi_aff_dim(pma, isl_dim_out);
	if (data->pos >= n_out) {
		isl_pw_multi_aff_free(pma);
		return 0;
	}

	pa = isl_pw_multi_aff_get_pw_aff(pma, data->pos);
	isl_pw_multi_aff_free(pma);

	data->res = isl_union_pw_aff_add_pw_aff(data->res, pa);

	return data->res ? 0 : -1;
}
