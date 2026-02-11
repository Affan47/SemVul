nag_dialog_response_cb (GtkDialog *dialog,
                        gint response,
                        gpointer user_data)
{
	NMConnectionEditor *self = NM_CONNECTION_EDITOR (user_data);

	gtk_widget_hide (GTK_WIDGET (dialog));
	if (response == GTK_RESPONSE_NO) {

		ok_button_clicked_save_connection (self);
	}
	g_signal_handler_disconnect (dialog, self->nag_id);
	self->nag_id = 0;
}
