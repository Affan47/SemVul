_gdict_show_gerror_dialog (GtkWidget   *widget,
			   const gchar *title,
			   GError      *error)
{
  g_return_if_fail (GTK_IS_WIDGET (widget));
  g_return_if_fail (title != NULL);
  g_return_if_fail (error != NULL);

  show_error_dialog (get_toplevel_window (widget), title, error->message);

  g_error_free (error);
}
