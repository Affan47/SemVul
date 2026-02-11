multiplexer_deliver_data (Multiplexer* self, gint channel, void* data, gint len) {
	FsoFrameworkLogger* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	gchar* _tmp3_ = NULL;
	gchar* _tmp4_ = NULL;
	Channel** _tmp5_ = NULL;
	gint _tmp5__length1 = 0;
	gint _tmp6_ = 0;
	Channel* _tmp7_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->logger;
	_tmp1_ = len;
	_tmp2_ = channel;
	_tmp3_ = g_strdup_printf ("0710 -> deliver %d bytes for channel %d", _tmp1_, _tmp2_);
	_tmp4_ = _tmp3_;
	fso_framework_logger_debug (_tmp0_, _tmp4_);
	_g_free0 (_tmp4_);
	_tmp5_ = self->priv->vc;
	_tmp5__length1 = self->priv->vc_length1;
	_tmp6_ = channel;
	_tmp7_ = _tmp5_[_tmp6_];
	if (_tmp7_ == NULL) {
		FsoFrameworkLogger* _tmp8_ = NULL;
		gboolean _tmp9_ = FALSE;
		_tmp8_ = self->priv->logger;
		_tmp9_ = fso_framework_logger_debug (_tmp8_, "Should deliver bytes for unknown channel: ignoring");
		_vala_assert (_tmp9_, "logger.debug( \"Should deliver bytes for unknown channel: ignoring\" )");
	} else {
		Channel** _tmp10_ = NULL;
		gint _tmp10__length1 = 0;
		gint _tmp11_ = 0;
		Channel* _tmp12_ = NULL;
		void* _tmp13_ = NULL;
		gint _tmp14_ = 0;
		_tmp10_ = self->priv->vc;
		_tmp10__length1 = self->priv->vc_length1;
		_tmp11_ = channel;
		_tmp12_ = _tmp10_[_tmp11_];
		_tmp13_ = data;
		_tmp14_ = len;
		channel_deliverData (_tmp12_, _tmp13_, _tmp14_);
	}
	multiplexer_clearPingResponseTimeout (self);
}
