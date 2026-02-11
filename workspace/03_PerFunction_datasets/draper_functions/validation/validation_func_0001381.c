mines_set_n_mines_limit (Mines* self) {
	gint max_mines = 0;
	GSettings* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	GSettings* _tmp2_ = NULL;
	gint _tmp3_ = 0;
	GSettings* _tmp4_ = NULL;
	gint _tmp5_ = 0;
	gint _tmp6_ = 0;
	GtkSpinButton* _tmp11_ = NULL;
	gint _tmp12_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->settings;
	_tmp1_ = g_settings_get_int (_tmp0_, MINES_KEY_XSIZE);
	_tmp2_ = self->priv->settings;
	_tmp3_ = g_settings_get_int (_tmp2_, MINES_KEY_YSIZE);
	max_mines = (_tmp1_ * _tmp3_) - 10;
	_tmp4_ = self->priv->settings;
	_tmp5_ = g_settings_get_int (_tmp4_, MINES_KEY_NMINES);
	_tmp6_ = max_mines;
	if (_tmp5_ > _tmp6_) {
		GSettings* _tmp7_ = NULL;
		gint _tmp8_ = 0;
		GtkSpinButton* _tmp9_ = NULL;
		gint _tmp10_ = 0;
		_tmp7_ = self->priv->settings;
		_tmp8_ = max_mines;
		g_settings_set_int (_tmp7_, MINES_KEY_NMINES, _tmp8_);
		_tmp9_ = self->priv->n_mines_spin;
		_tmp10_ = max_mines;
		gtk_spin_button_set_value (_tmp9_, (gdouble) _tmp10_);
	}
	_tmp11_ = self->priv->n_mines_spin;
	_tmp12_ = max_mines;
	gtk_spin_button_set_range (_tmp11_, (gdouble) 1, (gdouble) _tmp12_);
}
