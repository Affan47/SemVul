_folks_role_field_details___lambda37_ (FolksRoleFieldDetails* self, GObject* s, GParamSpec* p) {
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	gconstpointer _tmp2_ = NULL;
	FolksRole* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	const gchar* _tmp5_ = NULL;
	g_return_if_fail (s != NULL);
	g_return_if_fail (p != NULL);
	_tmp0_ = folks_abstract_field_details_get_id ((FolksAbstractFieldDetails*) self);
	_tmp1_ = _tmp0_;
	_tmp2_ = folks_abstract_field_details_get_value ((FolksAbstractFieldDetails*) self);
	_tmp3_ = _tmp2_;
	_tmp4_ = folks_role_get_uid ((FolksRole*) _tmp3_);
	_tmp5_ = _tmp4_;
	if (g_strcmp0 (_tmp1_, _tmp5_) != 0) {
		gconstpointer _tmp6_ = NULL;
		FolksRole* _tmp7_ = NULL;
		const gchar* _tmp8_ = NULL;
		const gchar* _tmp9_ = NULL;
		_tmp6_ = folks_abstract_field_details_get_value ((FolksAbstractFieldDetails*) self);
		_tmp7_ = _tmp6_;
		_tmp8_ = folks_role_get_uid ((FolksRole*) _tmp7_);
		_tmp9_ = _tmp8_;
		folks_abstract_field_details_set_id ((FolksAbstractFieldDetails*) self, _tmp9_);
	}
}
