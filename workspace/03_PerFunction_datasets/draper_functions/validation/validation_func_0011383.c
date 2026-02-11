tds_model_read_string (TDSModel* self, GInputStream* stream, GError** error) {
	gchar* result = NULL;
	GString* _tmp0_;
	GString* value;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (stream != NULL, NULL);
	_tmp0_ = g_string_new ("");
	value = _tmp0_;
	while (TRUE) {
		GInputStream* _tmp1_;
		guint8 _tmp2_ = 0U;
		guint8 c;
		guint8 _tmp3_;
		GString* _tmp7_;
		guint8 _tmp8_;
		_tmp1_ = stream;
		_tmp2_ = tds_model_read_uint8 (self, _tmp1_, &_inner_error_);
		c = _tmp2_;
		if (_inner_error_ != NULL) {
			g_propagate_error (error, _inner_error_);
			_g_string_free0 (value);
			return NULL;
		}
		_tmp3_ = c;
		if (((gint) _tmp3_) == 0) {
			GString* _tmp4_;
			const gchar* _tmp5_;
			gchar* _tmp6_;
			_tmp4_ = value;
			_tmp5_ = _tmp4_->str;
			_tmp6_ = g_strdup (_tmp5_);
			result = _tmp6_;
			_g_string_free0 (value);
			return result;
		}
		_tmp7_ = value;
		_tmp8_ = c;
		g_string_append_c (_tmp7_, (gchar) _tmp8_);
	}
	_g_string_free0 (value);
}
