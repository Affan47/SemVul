fso_framework_test_multi_signal_waiter_add_signal (FsoFrameworkTestMultiSignalWaiter* self, GObject* emitter, const gchar* signame, gint timeout) {
	FsoFrameworkTestSignalWrapper* s = NULL;
	GObject* _tmp0_ = NULL;
	GObject* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	gint _tmp4_ = 0;
	FsoFrameworkTestSignalWrapper* _tmp5_ = NULL;
	FsoFrameworkTestSignalWrapper* _tmp6_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (emitter != NULL);
	g_return_if_fail (signame != NULL);
	_tmp0_ = emitter;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_tmp2_ = signame;
	_tmp3_ = g_strdup (_tmp2_);
	_tmp4_ = timeout;
	_tmp5_ = fso_framework_test_signal_wrapper_new ();
	fso_framework_test_signal_wrapper_set_emitter (_tmp5_, _tmp1_);
	fso_framework_test_signal_wrapper_set_signame (_tmp5_, _tmp3_);
	fso_framework_test_signal_wrapper_set_timeout (_tmp5_, _tmp4_);
	s = _tmp5_;
	g_signal_connect_object (s, "triggered", (GCallback) ___lambda4__fso_framework_test_signal_wrapper_triggered, self, 0);
	_tmp6_ = _fso_framework_test_signal_wrapper_ref0 (s);
	self->priv->signals = g_list_append (self->priv->signals, _tmp6_);
	_fso_framework_test_signal_wrapper_unref0 (s);
}
