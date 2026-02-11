gtk_mult_update_timer (GtkMult* self) {
	gboolean result = FALSE;
	gboolean _tmp0_;
	gdouble _tmp1_;
	guint secs;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	gchar* text;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = mult_puzzle_get_is_done (self->priv->_puzzle);
	if (_tmp0_) {
		result = FALSE;
		return result;
	}
	_tmp1_ = g_timer_elapsed (self->priv->timer, NULL);
	secs = (guint) _tmp1_;
	_tmp2_ = _ ("Time");
	_tmp3_ = g_strdup_printf ("%s: %02u:%02u:%02u", _tmp2_, (secs / 60) / 60, (secs / 60) % 60, secs % 60);
	text = _tmp3_;
	gtk_label_set_text (self->priv->timer_label, text);
	result = TRUE;
	_g_free0 (text);
	return result;
}
