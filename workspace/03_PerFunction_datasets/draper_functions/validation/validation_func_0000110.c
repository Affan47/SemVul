abiDialogNew(const char * role, gboolean resizable)
{
  GtkWidget * dlg = gtk_dialog_new () ;
  if ( role )
    gtk_window_set_role ( GTK_WINDOW(dlg), role ) ;
  gtk_window_set_resizable ( GTK_WINDOW(dlg), resizable ) ;
  gtk_container_set_border_width ( GTK_CONTAINER (dlg), 5 ) ;
  gtk_box_set_spacing ( GTK_BOX ( gtk_dialog_get_content_area(GTK_DIALOG (dlg))), 2 ) ;
  return dlg ;
}
