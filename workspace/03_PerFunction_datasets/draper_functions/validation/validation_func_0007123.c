gsb_fyear_update_invalid ( GtkWidget *tree_view )
{
    GtkTreeModel *model;
    GtkTreeIter iter;


    gsb_data_fyear_check_all_for_invalid ();

    model = gtk_tree_view_get_model (GTK_TREE_VIEW (tree_view));


    if (!gtk_tree_model_get_iter_first ( model, &iter ))
	return;

    do
    {
	gint fyear_number;
	gchar *invalid;

	gtk_tree_model_get ( model, &iter,
			     FYEAR_NUMBER_COLUMN, &fyear_number,
			     -1 );
	if (gsb_data_fyear_get_invalid (fyear_number))
	    invalid = GTK_STOCK_DIALOG_WARNING;
	else
	    invalid = NULL;

	gtk_list_store_set ( GTK_LIST_STORE (model), &iter,
			     FYEAR_INVALID_COLUMN, invalid,
			     -1 );
    }
    while ( gtk_tree_model_iter_next ( model, &iter ));
}
