confirm_cancel_callback ( widget, data )
GtkWidget *widget;
gpointer data;
{
  ConfirmData *cd = (ConfirmData *) data;

  gtk_grab_remove ( cd->window );
  if ( cd->cancel_callback )
    cd->cancel_callback ( widget, (gpointer)cd->callback_data );
  gtk_widget_destroy ( cd->window );
  free ( cd );
}
