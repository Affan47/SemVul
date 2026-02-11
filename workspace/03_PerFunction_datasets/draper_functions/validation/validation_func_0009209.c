gsb_currency_link_config_add_link ( GtkWidget *tree_view )
{
    gint link_number;
    GtkTreeModel *model;
    GtkTreeIter iter;

    model = gtk_tree_view_get_model ( GTK_TREE_VIEW (tree_view));

    link_number = gsb_data_currency_link_new (0);


    gsb_data_currency_link_set_first_currency ( link_number,
						1 );
    gsb_data_currency_link_set_second_currency ( link_number,
						 1 );
    gsb_currency_link_config_append_line ( model,
					   link_number,
					   &iter );
    gtk_tree_selection_select_iter ( gtk_tree_view_get_selection (GTK_TREE_VIEW (tree_view)),
				     &iter );
    if ( etat.modification_fichier == 0 )
        modification_fichier ( TRUE );
    return FALSE;
}
