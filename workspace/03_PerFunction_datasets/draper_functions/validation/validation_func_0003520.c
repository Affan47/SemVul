bisho_pane_set_banner (BishoPane *pane, const char *message)
{
  if (message) {
    gtk_info_bar_set_message_type (GTK_INFO_BAR (pane->banner), GTK_MESSAGE_INFO);
    gtk_label_set_text (GTK_LABEL (pane->banner_label), message);
    gtk_widget_show (pane->banner);
    install_banner_hide (pane);
  } else {
    gtk_widget_hide (pane->banner);
  }
}
