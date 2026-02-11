test_ln (void) {
	{
		gint a;
		a = 1;
		{
			gboolean _tmp0_;
			_tmp0_ = TRUE;
			while (TRUE) {
				gboolean _tmp1_;
				gint _tmp3_;
				gint _tmp4_;
				Number* _tmp5_;
				Number* _tmp6_;
				Number* _tmp7_ = NULL;
				Number* _tmp8_;
				Number* z;
				gint _tmp9_;
				gdouble _tmp10_ = 0.0;
				gdouble expected;
				Number* _tmp11_;
				gdouble _tmp12_;
				gboolean _tmp13_ = FALSE;
				_tmp1_ = _tmp0_;
				if (!_tmp1_) {
					gint _tmp2_;
					_tmp2_ = a;
					a = _tmp2_ + 1;
				}
				_tmp0_ = FALSE;
				_tmp3_ = a;
				if (!(_tmp3_ <= 10)) {
					break;
				}
				_tmp4_ = a;
				_tmp5_ = number_new_double ((gdouble) _tmp4_);
				_tmp6_ = _tmp5_;
				_tmp7_ = number_ln (_tmp6_);
				_tmp8_ = _tmp7_;
				_number_unref0 (_tmp6_);
				z = _tmp8_;
				_tmp9_ = a;
				_tmp10_ = log ((gdouble) _tmp9_);
				expected = _tmp10_;
				_tmp11_ = z;
				_tmp12_ = expected;
				_tmp13_ = double_matches (_tmp11_, _tmp12_);
				if (!_tmp13_) {
					gint _tmp14_;
					Number* _tmp15_;
					gdouble _tmp16_ = 0.0;
					gdouble _tmp17_;
					gchar* _tmp18_ = NULL;
					gchar* _tmp19_;
					_tmp14_ = a;
					_tmp15_ = z;
					_tmp16_ = number_to_double (_tmp15_);
					_tmp17_ = expected;
					_tmp18_ = g_strdup_printf ("(%f).ln () -> %f, expected %f", (gdouble) _tmp14_, _tmp16_, _tmp17_);
					_tmp19_ = _tmp18_;
					fail (_tmp19_);
					_g_free0 (_tmp19_);
					_number_unref0 (z);
					return;
				}
				_number_unref0 (z);
			}
		}
	}
	pass (NULL);
}
