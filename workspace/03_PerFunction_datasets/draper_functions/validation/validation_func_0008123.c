on_branch_combo_changed (GtkComboBox *combo_box, GitLogPane *self)
{
	GtkTreeModel *log_branch_combo_model;
	gchar *branch;
	GtkTreeIter iter;
	gboolean active;

	log_branch_combo_model = gtk_combo_box_get_model (combo_box);

	if (gtk_combo_box_get_active_iter (combo_box, &iter))
	{
		gtk_tree_model_get (log_branch_combo_model, &iter,
		                    BRANCH_COL_ACTIVE, &active,
							BRANCH_COL_NAME, &branch,
							-1);

		self->priv->viewing_active_branch = active;

		g_free (self->priv->selected_branch);
		self->priv->selected_branch = g_strdup (branch);

		g_free (branch);


		refresh_log (self);
	}
}
