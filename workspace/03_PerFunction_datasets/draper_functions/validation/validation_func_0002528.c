mines_fullscreen_cb (Mines* self) {
	gboolean _tmp0_ = FALSE;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->is_fullscreen;
	if (_tmp0_) {
		GtkWindow* _tmp1_ = NULL;
		_tmp1_ = self->priv->window;
		gtk_window_unfullscreen (_tmp1_);
	} else {
		GtkWindow* _tmp2_ = NULL;
		_tmp2_ = self->priv->window;
		gtk_window_fullscreen (_tmp2_);
	}
}
