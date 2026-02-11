_dialog_response_cb (GtkDialog *dialog, gint response, gpointer data)
{
  FrogrCreateNewSetDialog *self = NULL;


  self = FROGR_CREATE_NEW_SET_DIALOG (dialog);
  if (response == GTK_RESPONSE_ACCEPT && _save_data (self) == FALSE)
    return;


  gtk_widget_destroy (GTK_WIDGET (dialog));
}
