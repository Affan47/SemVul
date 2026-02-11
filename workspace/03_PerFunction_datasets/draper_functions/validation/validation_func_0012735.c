pipeline_error_dlg (GtkWindow * parent,
    GSTPPipelineDescription * pipeline_desc, const gchar * error_message)
{
  gchar *errstr;

  if (error_message) {
    errstr = g_strdup_printf ("%s: %s", pipeline_desc->name, error_message);
  } else {
    errstr = g_strdup_printf (_("Failed to construct test pipeline for '%s'"),
        pipeline_desc->name);
  }

  if (parent == NULL) {
    g_printerr ("%s", errstr);
  } else {
    GtkWidget *dialog;

    dialog = gtk_message_dialog_new (parent,
        GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", errstr);

    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
  }

  g_free (errstr);
}
