channel_acked (Channel* self) {
	gchar* result = NULL;
	guint _tmp0_ = 0U;
	FsoFrameworkLogger* _tmp2_ = NULL;
	gboolean _tmp3_ = FALSE;
	FsoFrameworkTransport* _tmp4_ = NULL;
	gboolean _tmp5_ = FALSE;
	GSourceFunc _tmp12_ = NULL;
	void* _tmp12__target = NULL;
	FsoFrameworkTransport* _tmp17_ = NULL;
	gchar* _tmp18_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->ackTimeoutWatch;
	if (_tmp0_ > ((guint) 0)) {
		guint _tmp1_ = 0U;
		_tmp1_ = self->priv->ackTimeoutWatch;
		g_source_remove (_tmp1_);
	}
	_tmp2_ = self->priv->logger;
	_tmp3_ = fso_framework_logger_debug (_tmp2_, "Acked");
	_vala_assert (_tmp3_, "logger.debug( \"Acked\" )");
	_tmp4_ = self->priv->transport;
	_tmp5_ = fso_framework_transport_open (_tmp4_);
	if (!_tmp5_) {
		FsoFrameworkLogger* _tmp6_ = NULL;
		gint _tmp7_ = 0;
		const gchar* _tmp8_ = NULL;
		gchar* _tmp9_ = NULL;
		gchar* _tmp10_ = NULL;
		gchar* _tmp11_ = NULL;
		_tmp6_ = self->priv->logger;
		_tmp7_ = errno;
		_tmp8_ = strerror (_tmp7_);
		_tmp9_ = g_strdup_printf ("Could not open transport: %s", _tmp8_);
		_tmp10_ = _tmp9_;
		fso_framework_logger_error (_tmp6_, _tmp10_);
		_g_free0 (_tmp10_);
		_tmp11_ = g_strdup ("");
		result = _tmp11_;
		return result;
	}
	self->priv->_status = CHANNEL_STATUS_Acked;
	_tmp12_ = self->priv->ackCallback;
	_tmp12__target = self->priv->ackCallback_target;
	if (_tmp12_ != NULL) {
		FsoFrameworkLogger* _tmp13_ = NULL;
		gboolean _tmp14_ = FALSE;
		_tmp13_ = self->priv->logger;
		_tmp14_ = fso_framework_logger_debug (_tmp13_, "AckCallback is set, calling");
		_vala_assert (_tmp14_, "logger.debug( \"AckCallback is set, calling\" )");
		g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, ____lambda2__gsource_func, channel_ref (self), channel_unref);
	} else {
		FsoFrameworkLogger* _tmp15_ = NULL;
		gboolean _tmp16_ = FALSE;
		_tmp15_ = self->priv->logger;
		_tmp16_ = fso_framework_logger_debug (_tmp15_, "AckCallback NOT set");
		_vala_assert (_tmp16_, "logger.debug( \"AckCallback NOT set\" )");
	}
	_tmp17_ = self->priv->transport;
	_tmp18_ = fso_framework_transport_getName (_tmp17_);
	result = _tmp18_;
	return result;
}
