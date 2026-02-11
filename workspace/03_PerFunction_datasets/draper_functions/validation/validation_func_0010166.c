isl_space_wrap(__isl_take isl_space *dim)
{
	isl_space *wrap;

	if (!dim)
		return NULL;

	wrap = isl_space_set_alloc(dim->ctx,
				    dim->nparam, dim->n_in + dim->n_out);

	wrap = copy_ids(wrap, isl_dim_param, 0, dim, isl_dim_param);
	wrap = copy_ids(wrap, isl_dim_set, 0, dim, isl_dim_in);
	wrap = copy_ids(wrap, isl_dim_set, dim->n_in, dim, isl_dim_out);

	if (!wrap)
		goto error;

	wrap->nested[1] = dim;

	return wrap;
error:
	isl_space_free(dim);
	return NULL;
}
