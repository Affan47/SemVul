fso_gsm_lib_gsm0710mux_transport_real_read (FsoFrameworkTransport* base, void* data, gint length) {
	FsoGsmLibGsm0710muxTransport * self;
	gint result = 0;
	gint _tmp0_ = 0;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	void* _tmp3_ = NULL;
	gchar* _tmp4_ = NULL;
	gint _tmp4__length1 = 0;
	gint _tmp5_ = 0;
	gint l = 0;
	gint _tmp6_ = 0;
	self = (FsoGsmLibGsm0710muxTransport*) base;
	_tmp0_ = self->priv->length;
	_vala_assert (_tmp0_ > 0, "this.length > 0");
	_tmp1_ = self->priv->length;
	_tmp2_ = length;
	_vala_assert (_tmp1_ < _tmp2_, "this.length < length");
	_tmp3_ = data;
	_tmp4_ = self->priv->muxbuffer;
	_tmp4__length1 = self->priv->muxbuffer_length1;
	_tmp5_ = self->priv->length;
	memcpy (_tmp3_, _tmp4_, (gsize) _tmp5_);
	_tmp6_ = self->priv->length;
	l = _tmp6_;
	self->priv->length = 0;
	result = l;
	return result;
}
