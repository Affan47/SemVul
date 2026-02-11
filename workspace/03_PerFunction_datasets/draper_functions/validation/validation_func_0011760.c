dialog_response (GtkWidget * widget, GtkResponseType response, gpointer data)
{
  GSMColorButton *color_button = GSM_COLOR_BUTTON (data);
  GtkColorChooser *color_chooser;

  if (response == GTK_RESPONSE_OK) {
    color_chooser = GTK_COLOR_CHOOSER (color_button->priv->cc_dialog);

    gtk_color_chooser_get_rgba (color_chooser, &color_button->priv->color);

    gtk_widget_hide (color_button->priv->cc_dialog);

    gtk_widget_queue_draw (GTK_WIDGET (&color_button->widget));

    g_signal_emit (color_button, color_button_signals[COLOR_SET], 0);

    g_object_freeze_notify (G_OBJECT (color_button));
    g_object_notify (G_OBJECT (color_button), "color");
    g_object_thaw_notify (G_OBJECT (color_button));
  }
  else
    gtk_widget_hide (color_button->priv->cc_dialog);
}
