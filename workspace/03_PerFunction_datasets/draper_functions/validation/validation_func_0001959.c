___lambda34_ (GeeArrayList* x) {
	gboolean result = FALSE;
	GeeArrayList* _tmp0_ = NULL;
	GeeArrayList* _tmp1_ = NULL;
	g_return_val_if_fail (x != NULL, FALSE);
	_tmp0_ = gee_hazard_pointer__global_to_free;
	_tmp1_ = x;
	gee_array_list_add_all (_tmp0_, (GeeCollection*) _tmp1_);
	result = TRUE;
	_g_object_unref0 (x);
	return result;
}
