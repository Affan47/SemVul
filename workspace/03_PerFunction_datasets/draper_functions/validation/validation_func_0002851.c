go_data_vector_get_markup (GODataVector *vec, unsigned i)
{
	GODataVectorClass const *klass = GO_DATA_VECTOR_GET_CLASS (vec);

	g_return_val_if_fail (klass != NULL, NULL);
	if (! (vec->base.flags & GO_DATA_VECTOR_LEN_CACHED)) {
		(*klass->load_len) (vec);
		g_return_val_if_fail (vec->base.flags & GO_DATA_VECTOR_LEN_CACHED, NULL);
	}
	g_return_val_if_fail ((int)i < vec->len, NULL);

	return (klass->get_markup)? (*klass->get_markup) (vec, i): NULL;
}
