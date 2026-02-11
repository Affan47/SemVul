clocks_analog_frame_calculate_diameter (ClocksAnalogFrame* self) {
	gint result = 0;
	gint ret = 0;
	GtkWidget* child = NULL;
	GtkWidget* _tmp0_ = NULL;
	GtkWidget* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	GtkWidget* _tmp3_ = NULL;
	gboolean _tmp7_ = FALSE;
	g_return_val_if_fail (self != NULL, 0);
	ret = 2 * CLOCKS_ANALOG_FRAME_RADIUS_PAD;
	_tmp0_ = gtk_bin_get_child ((GtkBin*) self);
	_tmp1_ = _g_object_ref0 (_tmp0_);
	child = _tmp1_;
	_tmp3_ = child;
	if (_tmp3_ != NULL) {
		GtkWidget* _tmp4_ = NULL;
		gboolean _tmp5_ = FALSE;
		gboolean _tmp6_ = FALSE;
		_tmp4_ = child;
		_tmp5_ = gtk_widget_get_visible (_tmp4_);
		_tmp6_ = _tmp5_;
		_tmp2_ = _tmp6_;
	} else {
		_tmp2_ = FALSE;
	}
	_tmp7_ = _tmp2_;
	if (_tmp7_) {
		gint w = 0;
		gint h = 0;
		GtkWidget* _tmp8_ = NULL;
		gint _tmp9_ = 0;
		GtkWidget* _tmp10_ = NULL;
		gint _tmp11_ = 0;
		gint _tmp12_ = 0;
		gint _tmp13_ = 0;
		gint _tmp14_ = 0;
		gint _tmp15_ = 0;
		gint _tmp16_ = 0;
		gdouble _tmp17_ = 0.0;
		_tmp8_ = child;
		gtk_widget_get_preferred_width (_tmp8_, &_tmp9_, NULL);
		w = _tmp9_;
		_tmp10_ = child;
		gtk_widget_get_preferred_height (_tmp10_, &_tmp11_, NULL);
		h = _tmp11_;
		_tmp12_ = ret;
		_tmp13_ = w;
		_tmp14_ = w;
		_tmp15_ = h;
		_tmp16_ = h;
		_tmp17_ = sqrt ((gdouble) ((_tmp13_ * _tmp14_) + (_tmp15_ * _tmp16_)));
		ret = _tmp12_ + ((gint) _tmp17_);
	}
	result = ret;
	_g_object_unref0 (child);
	return result;
}
