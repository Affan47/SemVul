set_new_default_account(GtkTreeModel *model,
					GtkTreePath  *path,
					GtkTreeIter  *iter,
					gint	     *account_id)
{
	PrefsAccount *account = NULL;
	PangoWeight weight;

	gtk_tree_model_get(model, iter,
			   ACCOUNT_DATA, &account,
			   -1);

	if (*account_id == account->account_id)
		weight = PANGO_WEIGHT_NORMAL;
	else
		weight = PANGO_WEIGHT_BOLD;

	gtk_list_store_set(GTK_LIST_STORE(model), iter,
			   ACCOUNT_IS_DEFAULT, weight, -1);

	return FALSE;
}
