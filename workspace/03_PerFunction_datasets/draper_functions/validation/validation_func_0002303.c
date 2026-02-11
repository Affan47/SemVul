exo_icon_chooser_dialog_screen_changed (GtkWidget *widget,
                                        GdkScreen *previous_screen)
{

  if (GTK_WIDGET_CLASS (exo_icon_chooser_dialog_parent_class)->screen_changed != NULL)
    (*GTK_WIDGET_CLASS (exo_icon_chooser_dialog_parent_class)->screen_changed) (widget, previous_screen);


  exo_icon_chooser_dialog_set_model (EXO_ICON_CHOOSER_DIALOG (widget));
}
