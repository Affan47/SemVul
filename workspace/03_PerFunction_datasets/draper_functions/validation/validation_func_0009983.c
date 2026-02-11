callback_resize_aux_layers_button_set_sensitive (GtkWidget * button,
						 gpointer data)
{
  PresDiscStatus *pd_status = PRESDISC_STATUS (data);
  PlugInUIVals *ui = PLUGIN_UI_VALS (pd_status->ui_vals);
  if ((ui->pres_status == TRUE) || (ui->disc_status == TRUE)
      || (ui->rigmask_status == TRUE))
    {
      gtk_widget_set_sensitive ((GtkWidget *) (pd_status->button), TRUE);
    }
  else
    {
      gtk_widget_set_sensitive ((GtkWidget *) (pd_status->button), FALSE);
    }
}
