scan_0D(struct isl_basic_set *bset,
	struct isl_scan_callback *callback)
{
	struct isl_vec *sample;

	sample = isl_vec_alloc(bset->ctx, 1);
	isl_basic_set_free(bset);

	if (!sample)
		return -1;

	isl_int_set_si(sample->el[0], 1);

	return callback->add(callback, sample);
}
