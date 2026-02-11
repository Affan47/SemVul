prefs_account_set_string_from_combobox(PrefParam *pparam)
{
	GtkWidget *combobox;
	GtkListStore *menu;
	GtkTreeIter iter;
	gchar **str;

	cm_return_if_fail(*pparam->widget != NULL);

	combobox = *pparam->widget;
	cm_return_if_fail(gtk_combo_box_get_active_iter(
				GTK_COMBO_BOX(combobox), &iter));

	str = (gchar **)pparam->data;
	g_free(*str);
	menu = GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combobox)));
	gtk_tree_model_get(GTK_TREE_MODEL(menu), &iter,
			COMBOBOX_PRIVACY_PLUGIN_ID, &(*str),
			-1);
}
