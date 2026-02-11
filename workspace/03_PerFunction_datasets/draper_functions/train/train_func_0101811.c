gpk_modal_dialog_button_close_cb (GtkWidget *widget_button, GpkModalDialog *dialog)
{
	dialog->priv->response = GTK_RESPONSE_CLOSE;
	g_main_loop_quit (dialog->priv->loop);

	if (dialog->priv->pulse_timer_id != 0) {
		g_source_remove (dialog->priv->pulse_timer_id);
		dialog->priv->pulse_timer_id = 0;
	}

	gpk_animated_icon_enable_animation (GPK_ANIMATED_ICON (dialog->priv->image_status), FALSE);
	if (g_main_loop_is_running (dialog->priv->loop))
		g_main_loop_quit (dialog->priv->loop);
	else
		g_signal_emit (dialog, signals [GPK_MODAL_DIALOG_CLOSE], 0);
}
