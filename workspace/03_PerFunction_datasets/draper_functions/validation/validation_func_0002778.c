gpk_update_viewer_detail_button_pressed (GtkWidget *treeview, GdkEventButton *event, gpointer user_data)
{
	GtkTreeSelection *selection;
	GtkTreePath *path;


	if (event->type != GDK_BUTTON_PRESS || event->button != 3) {

		return FALSE;
	}

	g_debug ("Single right click on the tree view");


	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW(treeview));
	if (gtk_tree_selection_count_selected_rows (selection) <= 1) {

		if (gtk_tree_view_get_path_at_pos (GTK_TREE_VIEW(treeview),
						   (gint) event->x, (gint) event->y, &path,
						   NULL, NULL, NULL)) {
			gtk_tree_selection_unselect_all (selection);
			gtk_tree_selection_select_path (selection, path);
			gtk_tree_path_free (path);
		}
	}


	gpk_update_viewer_detail_popup_menu_create (treeview, event, NULL);
	return TRUE;
}
