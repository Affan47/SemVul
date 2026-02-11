fso_framework_bin_builder_append_custom (FsoFrameworkBinBuilder* self, guint64 val, gint size) {
	g_return_if_fail (self != NULL);
	{
		gint i = 0;
		gint _tmp0_ = 0;
		_tmp0_ = size;
		i = _tmp0_ - 1;
		{
			gboolean _tmp1_ = FALSE;
			_tmp1_ = TRUE;
			while (TRUE) {
				gboolean _tmp2_ = FALSE;
				gint _tmp4_ = 0;
				guint64 _tmp5_ = 0ULL;
				gint _tmp6_ = 0;
				guint8 _tmp7_ = 0U;
				_tmp2_ = _tmp1_;
				if (!_tmp2_) {
					gint _tmp3_ = 0;
					_tmp3_ = i;
					i = _tmp3_ - 1;
				}
				_tmp1_ = FALSE;
				_tmp4_ = i;
				if (!(_tmp4_ >= 0)) {
					break;
				}
				_tmp5_ = val;
				_tmp6_ = i;
				_tmp7_ = fso_framework_bin_builder_nth_byte (_tmp5_, (guint) _tmp6_);
				self->_data = g_list_append (self->_data, (gpointer) ((guintptr) _tmp7_));
			}
		}
	}
	fso_framework_bin_builder_append_align (self);
}
