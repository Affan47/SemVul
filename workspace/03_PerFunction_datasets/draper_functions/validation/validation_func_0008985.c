unity_deprecated_scope_queue_search_changed (UnityDeprecatedScope* self, UnitySearchType search_type) {
	UnitySearchType _tmp0_ = 0;
	UnityInternalDeprecatedScopeImpl* pimpl = NULL;
	GObject* _tmp1_ = NULL;
	UnityInternalDeprecatedScopeImpl* _tmp2_ = NULL;
	UnitySearchType _tmp3_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = search_type;
	g_return_if_fail (_tmp0_ < UNITY_SEARCH_TYPE_N_TYPES);
	_tmp1_ = unity_deprecated_scope_base_get_impl ((UnityDeprecatedScopeBase*) self);
	_tmp2_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp1_, UNITY_INTERNAL_TYPE_DEPRECATED_SCOPE_IMPL) ? ((UnityInternalDeprecatedScopeImpl*) _tmp1_) : NULL);
	pimpl = _tmp2_;
	_tmp3_ = search_type;
	unity_internal_deprecated_scope_impl_queue_search_for_type (pimpl, _tmp3_);
	_g_object_unref0 (pimpl);
}
