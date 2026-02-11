ui_auto_separator_add_ref(GeanyAutoSeparator *autosep, GtkWidget *item)
{

	if (autosep->item_count == 0)
		g_signal_connect(autosep->widget, "destroy",
			G_CALLBACK(gtk_widget_destroyed), &autosep->widget);

	if (GTK_WIDGET_VISIBLE(item))
		autosep->show_count++;

	autosep->item_count++;
	auto_separator_update(autosep);

	g_signal_connect(item, "show", G_CALLBACK(on_auto_separator_item_show_hide), autosep);
	g_signal_connect(item, "hide", G_CALLBACK(on_auto_separator_item_show_hide), autosep);
	g_signal_connect(item, "destroy", G_CALLBACK(on_auto_separator_item_destroy), autosep);
}
