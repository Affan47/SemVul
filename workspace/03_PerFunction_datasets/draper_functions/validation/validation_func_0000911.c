response_cb (GtkDialog *dialog, gint id, gpointer data)
{
  charpick_data *curr_data = data;

  if(id == GTK_RESPONSE_HELP){
    phelp_cb (dialog,id,data);
    return;
  }

  gtk_widget_destroy (curr_data->propwindow);
  curr_data->propwindow = NULL;

}
