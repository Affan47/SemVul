transport_sel_cb(GtkMenuItem *menuitem, gpointer data)
{
	struct SpamAssassinPage *page = (struct SpamAssassinPage *) data;
	struct Transport *transport;
	GtkTreeModel *model;
	GtkTreeIter iter;

	cm_return_if_fail(gtk_combo_box_get_active_iter(
			GTK_COMBO_BOX(page->transport_optmenu), &iter));

	model = gtk_combo_box_get_model(GTK_COMBO_BOX(page->transport_optmenu));
	gtk_tree_model_get(model, &iter, 1, &transport, -1);

	show_transport(page, transport);
}
