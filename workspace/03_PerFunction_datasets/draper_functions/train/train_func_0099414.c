glade_palette_new_item (GladePalette * palette, GladeWidgetAdaptor * adaptor)
{
  GtkWidget *item, *button, *label, *box;

  item = (GtkWidget *) gtk_toggle_tool_button_new ();
  g_object_set_data (G_OBJECT (item), "glade-widget-adaptor", adaptor);
  g_object_set_data (G_OBJECT (item), "glade-palette", palette);

  button = gtk_bin_get_child (GTK_BIN (item));
  g_assert (GTK_IS_BUTTON (button));


  box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  label = gtk_label_new (glade_widget_adaptor_get_title (adaptor));
  gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
  gtk_widget_show (label);
  gtk_widget_show (box);
  gtk_container_add (GTK_CONTAINER (box), label);
  gtk_tool_button_set_label_widget (GTK_TOOL_BUTTON (item), box);
  palette_item_refresh_cb (palette, item);


  g_signal_connect (G_OBJECT (item), "toggled",
                    G_CALLBACK (palette_item_toggled_cb), palette);


  g_signal_connect (G_OBJECT (palette), "refresh",
		    G_CALLBACK (palette_item_refresh_cb), item);


  g_signal_connect (G_OBJECT (button), "button-press-event",
                    G_CALLBACK (palette_item_button_press_cb), item);
  g_signal_connect_object (button, "drag-begin",
                           G_CALLBACK (glade_palette_drag_begin), adaptor, 0);
  g_signal_connect_object (button, "drag-data-get",
                           G_CALLBACK (glade_palette_drag_data_get), adaptor, 0);

  gtk_drag_source_set (button, GDK_BUTTON1_MASK, _glade_dnd_get_target (), 1, 0);

  gtk_widget_show (item);

  g_hash_table_insert (palette->priv->button_table,
		       (gchar *)glade_widget_adaptor_get_name (adaptor),
		       item);

  return item;
}
