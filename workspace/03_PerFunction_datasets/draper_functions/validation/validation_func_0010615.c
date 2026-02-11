functions_tests_my_hashable_real_equal_to (GeeHashable* base, FunctionsTestsMyHashable* hash) {
	FunctionsTestsMyHashable * self;
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	gint _tmp1_ = 0;
	FunctionsTestsMyHashable* _tmp2_ = NULL;
	gint _tmp3_ = 0;
	gboolean _tmp5_ = FALSE;
	self = (FunctionsTestsMyHashable*) base;
	g_return_val_if_fail (hash != NULL, FALSE);
	_tmp1_ = self->priv->i;
	_tmp2_ = hash;
	_tmp3_ = _tmp2_->priv->i;
	if (_tmp1_ == _tmp3_) {
		gint _tmp4_ = 0;
		_tmp4_ = self->priv->i;
		_tmp0_ = _tmp4_ != (-1);
	} else {
		_tmp0_ = FALSE;
	}
	_tmp5_ = _tmp0_;
	result = _tmp5_;
	return result;
}
