gee_sorted_map_empty (GType k_type, GBoxedCopyFunc k_dup_func, GDestroyNotify k_destroy_func, GType v_type, GBoxedCopyFunc v_dup_func, GDestroyNotify v_destroy_func) {
	GeeMap* result = NULL;
	GeeTreeMap* _tmp0_ = NULL;
	GeeTreeMap* _tmp1_ = NULL;
	GeeBidirSortedMap* _tmp2_ = NULL;
	GeeBidirSortedMap* _tmp3_ = NULL;
	GeeMap* _tmp4_ = NULL;
	_tmp0_ = gee_tree_map_new (k_type, (GBoxedCopyFunc) k_dup_func, k_destroy_func, v_type, (GBoxedCopyFunc) v_dup_func, v_destroy_func, NULL, NULL, NULL, NULL, NULL, NULL);
	_tmp1_ = _tmp0_;
	_tmp2_ = gee_abstract_bidir_sorted_map_get_read_only_view ((GeeAbstractBidirSortedMap*) _tmp1_);
	_tmp3_ = _tmp2_;
	_tmp4_ = (GeeMap*) _tmp3_;
	_g_object_unref0 (_tmp1_);
	result = _tmp4_;
	return result;
}
