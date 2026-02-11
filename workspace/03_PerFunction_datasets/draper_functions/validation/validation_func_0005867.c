exo_icon_view_search_ensure_directory (ExoIconView *icon_view)
{
  GtkWidget *toplevel;
  GtkWidget *frame;
  GtkWidget *vbox;


  toplevel = gtk_widget_get_toplevel (GTK_WIDGET (icon_view));


  if (G_LIKELY (icon_view->priv->search_window != NULL))
    {
      if (GTK_WINDOW (toplevel)->group != NULL)
        gtk_window_group_add_window (GTK_WINDOW (toplevel)->group, GTK_WINDOW (icon_view->priv->search_window));
      else if (GTK_WINDOW (icon_view->priv->search_window)->group != NULL)
        gtk_window_group_remove_window (GTK_WINDOW (icon_view->priv->search_window)->group, GTK_WINDOW (icon_view->priv->search_window));
      return;
    }


  icon_view->priv->search_window = gtk_window_new (GTK_WINDOW_POPUP);
  if (GTK_WINDOW (toplevel)->group != NULL)
    gtk_window_group_add_window (GTK_WINDOW (toplevel)->group, GTK_WINDOW (icon_view->priv->search_window));
  gtk_window_set_modal (GTK_WINDOW (icon_view->priv->search_window), TRUE);
  gtk_window_set_screen (GTK_WINDOW (icon_view->priv->search_window), gtk_widget_get_screen (GTK_WIDGET (icon_view)));


  g_signal_connect (G_OBJECT (icon_view->priv->search_window), "delete-event", G_CALLBACK (exo_icon_view_search_delete_event), icon_view);
  g_signal_connect (G_OBJECT (icon_view->priv->search_window), "scroll-event", G_CALLBACK (exo_icon_view_search_scroll_event), icon_view);
  g_signal_connect (G_OBJECT (icon_view->priv->search_window), "key-press-event", G_CALLBACK (exo_icon_view_search_key_press_event), icon_view);
  g_signal_connect (G_OBJECT (icon_view->priv->search_window), "button-press-event", G_CALLBACK (exo_icon_view_search_button_press_event), icon_view);


  frame = g_object_new (GTK_TYPE_FRAME, "shadow-type", GTK_SHADOW_ETCHED_IN, NULL);
  gtk_container_add (GTK_CONTAINER (icon_view->priv->search_window), frame);
  gtk_widget_show (frame);


  vbox = g_object_new (GTK_TYPE_VBOX, "border-width", 3, NULL);
  gtk_container_add (GTK_CONTAINER (frame), vbox);
  gtk_widget_show (vbox);


  icon_view->priv->search_entry = gtk_entry_new ();
  g_signal_connect (G_OBJECT (icon_view->priv->search_entry), "activate", G_CALLBACK (exo_icon_view_search_activate), icon_view);
  g_signal_connect (G_OBJECT (GTK_ENTRY (icon_view->priv->search_entry)->im_context), "preedit-changed",
                    G_CALLBACK (exo_icon_view_search_preedit_changed), icon_view);
  gtk_box_pack_start (GTK_BOX (vbox), icon_view->priv->search_entry, TRUE, TRUE, 0);
  gtk_widget_realize (icon_view->priv->search_entry);
  gtk_widget_show (icon_view->priv->search_entry);
}
