__lambda13_ (Block7Data* _data7_) {
	Profile * self;
	GVariant* _tmp0_ = NULL;
	GVariant* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	GVariant* _tmp3_ = NULL;
	GVariant* _tmp4_ = NULL;
	self = _data7_->self;
	_tmp0_ = g_action_get_state ((GAction*) _data7_->action);
	_tmp1_ = _tmp0_;
	_tmp2_ = g_variant_get_boolean (_tmp1_);
	_tmp3_ = g_variant_new_boolean (!_tmp2_);
	g_variant_ref_sink (_tmp3_);
	_tmp4_ = _tmp3_;
	g_signal_emit_by_name (_data7_->action, "change-state", _tmp4_);
	_g_variant_unref0 (_tmp4_);
	_g_variant_unref0 (_tmp1_);
}
