brasero_data_disc_rename_activated (BraseroDataDisc *disc)
{
	BraseroDataDiscPrivate *priv;
	GtkTreeSelection *selection;
	GtkTreeViewColumn *column;
	GtkTreePath *treepath;
	GList *list;

	priv = BRASERO_DATA_DISC_PRIVATE (disc);

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (priv->tree));

	list = gtk_tree_selection_get_selected_rows (selection, NULL);
	if (g_list_length (list) == 1) {
		gboolean is_imported;
		GtkTreeIter iter;

		treepath = list->data;
		g_list_free (list);

		if (!gtk_tree_model_get_iter (GTK_TREE_MODEL (priv->project), &iter, treepath)) {
			gtk_tree_path_free (treepath);
			return;
		}

		gtk_tree_model_get (GTK_TREE_MODEL (priv->project), &iter,
				    BRASERO_DATA_TREE_MODEL_IS_IMPORTED, &is_imported,
				    -1);
		if (is_imported) {
			gtk_tree_path_free (treepath);
			return;
		}

		column = gtk_tree_view_get_column (GTK_TREE_VIEW (priv->tree), 0);


		gtk_widget_grab_focus (priv->tree);
		gtk_tree_view_set_cursor_on_cell (GTK_TREE_VIEW (priv->tree),
						  treepath,
						  column,
						  NULL,
						  TRUE);
		gtk_tree_path_free (treepath);
	}
	else {
		gchar *string;
		GtkWidget *frame;
		GtkWidget *dialog;
		GtkWidget *rename;
		GtkResponseType answer;

		dialog = gtk_dialog_new_with_buttons (_("File Renaming"),
						      GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (disc))),
						      GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT,
						      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
						      _("_Rename"), GTK_RESPONSE_APPLY,
						      NULL);
		rename = brasero_rename_new ();
		brasero_rename_set_show_keep_default (BRASERO_RENAME (rename), FALSE);
		gtk_widget_show (rename);

		string = g_strdup_printf ("<b>%s</b>", _("Renaming mode"));
		frame = brasero_utils_pack_properties (string, rename, NULL);
		g_free (string);

		gtk_widget_show (frame);

		gtk_box_pack_start (GTK_BOX (gtk_dialog_get_content_area (GTK_DIALOG (dialog))), frame, TRUE, TRUE, 0);
		gtk_widget_show (dialog);

		answer = gtk_dialog_run (GTK_DIALOG (dialog));
		if (answer != GTK_RESPONSE_APPLY) {
			gtk_widget_destroy (dialog);
			return;
		}

		brasero_rename_do (BRASERO_RENAME (rename),
				   gtk_tree_view_get_selection (GTK_TREE_VIEW (priv->tree)),
				   BRASERO_DATA_TREE_MODEL_NAME,
				   brasero_data_disc_mass_rename_cb);

		gtk_widget_destroy (dialog);
	}
}
