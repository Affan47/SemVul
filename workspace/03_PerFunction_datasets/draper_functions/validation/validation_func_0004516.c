tip_show(CollectTable *ct)
{
	GtkWidget *label;
	gint x, y;

	if (ct->tip_window) return;

	gdk_window_get_pointer(ct->listview->window, &x, &y, NULL);

	ct->tip_info = collection_table_find_data_by_coord(ct, x, y, NULL);
	if (!ct->tip_info) return;

	ct->tip_window = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_window_set_resizable(GTK_WINDOW(ct->tip_window), FALSE);
	gtk_container_set_border_width(GTK_CONTAINER(ct->tip_window), 2);

	label = gtk_label_new(ct->show_text ? ct->tip_info->fd->path : ct->tip_info->fd->name);

	g_object_set_data(G_OBJECT(ct->tip_window), "tip_label", label);
	gtk_container_add(GTK_CONTAINER(ct->tip_window), label);
	gtk_widget_show(label);

	gdk_window_get_pointer(NULL, &x, &y, NULL);

#if GTK_CHECK_VERSION(2,20,0)
	if (!gtk_widget_get_realized(ct->tip_window)) gtk_widget_realize(ct->tip_window);
#else
	if (!GTK_WIDGET_REALIZED(ct->tip_window)) gtk_widget_realize(ct->tip_window);
#endif
	gtk_window_move(GTK_WINDOW(ct->tip_window), x + 16, y + 16);
	gtk_widget_show(ct->tip_window);
}
