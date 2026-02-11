banlist_copyentry (GtkWidget *menuitem, GtkTreeView *view)
{
	GtkTreeModel *model;
	GtkTreeSelection *sel;
	GtkTreeIter iter;
	GValue mask;
	GValue from;
	GValue date;
	char *str;

	memset (&mask, 0, sizeof (mask));
	memset (&from, 0, sizeof (from));
	memset (&date, 0, sizeof (date));


	sel = gtk_tree_view_get_selection (view);
	gtk_tree_selection_set_mode (sel, GTK_SELECTION_SINGLE);
	if (gtk_tree_selection_get_selected (sel, &model, &iter))
	{
		gtk_tree_model_get_value (model, &iter, MASK_COLUMN, &mask);
		gtk_tree_model_get_value (model, &iter, FROM_COLUMN, &from);
		gtk_tree_model_get_value (model, &iter, DATE_COLUMN, &date);


		if (strcmp (_("Copy mask"), gtk_menu_item_get_label (GTK_MENU_ITEM(menuitem))) == 0)
			str = g_value_dup_string (&mask);
		else
			str = g_strdup_printf (_("%s on %s by %s"), g_value_get_string (&mask),
								g_value_get_string (&date), g_value_get_string (&from));

		if (str[0] != 0)
			gtkutil_copy_to_clipboard (menuitem, NULL, str);

		g_value_unset (&mask);
		g_value_unset (&from);
		g_value_unset (&date);
		g_free (str);
	}
	gtk_tree_selection_set_mode (sel, GTK_SELECTION_MULTIPLE);
}
